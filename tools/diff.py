import click
import logging
import subprocess

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

@main.command()
@click.option('--binary', required=True)
@click.option('--gen', required=True)
def run(binary, gen):
    command = [
        gen,
        '>data.in',
        '&&',
        binary,
        '<data.in',
    ]
    while True:
        print(subprocess.check_output(command))

if __name__ == '__main__':
    main()
