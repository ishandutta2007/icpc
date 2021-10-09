import click
import filecmp
import logging
import subprocess
import time

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

@main.command()
@click.option('--gen', required=True)
@click.option('--binary', required=True)
@click.option('--good', default=None)
@click.option('--num-iterations', default=100)
@click.option('--time-interval', default=0.0)
def run(gen, binary, good, num_iterations, time_interval):
    for iteration in range(num_iterations):
        logging.info('iteration: {}'.format(iteration))
        with open('data.in', 'w') as f:
            subprocess.run(gen, stdout=f, check=True)
        with open('data.in', 'r') as f:
            with open('data.out', 'w') as g:
                subprocess.run(binary, stdin=f, stdout=g, check=True)
        if good:
            with open('data.in', 'r') as f:
                with open('good.out', 'w') as g:
                    subprocess.run(good, stdin=f, stdout=g, check=True)
            if not filecmp.cmp('data.out', 'good.out'):
                logging.error('Difference catched.')
                return
        if time_interval > 0.0:
            time.sleep(time_interval)

if __name__ == '__main__':
    main()
