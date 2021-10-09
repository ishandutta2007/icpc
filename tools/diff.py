import click
import logging
import subprocess
import time

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

@main.command()
@click.option('--binary', required=True)
@click.option('--gen', required=True)
@click.option('--num-iteration', default=100)
@click.option('--time-interval', default=0.0)
def run(binary, gen, num_iteration, time_interval):
    for _ in range(num_iteration):
        with open('data.in', 'w') as f:
            subprocess.run(gen, stdout=f, check=True)
        with open('data.in', 'r') as f:
            subprocess.run(binary, stdin=f, check=True)
        if time_interval > 0.0:
            time.sleep(time_interval)

if __name__ == '__main__':
    main()
