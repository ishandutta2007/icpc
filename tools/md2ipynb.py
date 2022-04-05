import click
import logging
import subprocess
import notedown

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)


@main.command()
@click.option('--source', required=True)
@click.option('--target', required=True)
def convert(source, target):
    with open(target, 'w') as output_handle:
        subprocess.run(['notedown', source], stdout=output_handle, check=True)


if __name__ == '__main__':
    main()
