import click
import glob
import logging
import notedown
import pathlib
import subprocess


def convert_internal(source, target):
    with open(target, 'w') as output_handle:
        subprocess.run(['notedown', source], stdout=output_handle, check=True)


@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)


@main.command()
@click.option('--source', required=True)
@click.option('--target', required=True)
def convert(source, target):
    convert_internal(source, target)


@main.command()
@click.option('--data-dir', required=True)
def generate_all(data_dir):
    for markdown_path in glob.glob(data_dir + "/*.md"):
        logging.info('Processing {}'.format(markdown_path))
        generated_dir = pathlib.Path(markdown_path).parent / 'generated'
        output_path = generated_dir / (pathlib.Path(markdown_path).name + ".ipynb")
        generated_dir.mkdir(exist_ok=True)
        output_path.touch(exist_ok=True)
        convert_internal(markdown_path, output_path)


if __name__ == '__main__':
    main()
