import click
import logging
import subprocess
import time
import filecmp

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

@main.command()
@click.option('--gen', required=True)
@click.option('--binary', required=True)
@click.option('--good', default=None)
@click.option('--num-iteration', default=100)
@click.option('--time-interval', default=0.0)
def run(gen, binary, good, num_iteration, time_interval):
    for _ in range(num_iteration):
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
                    logging.ERROR('Catch!!!')
                    return
        if time_interval > 0.0:
            time.sleep(time_interval)

if __name__ == '__main__':
    main()
