import click
import logging
import pathlib
import random

SCRIPT_DIR = pathlib.Path(__file__).parent.absolute()

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

@main.command()
def any():
    for path in (SCRIPT_DIR / 'data' / 'hints').iterdir():
        logging.info(str(path))
        with open(path, 'r') as f:
            lines = f.readlines()
        for line in lines:
            print(line.strip())
        print()

@main.command()
def idea():
    with open(SCRIPT_DIR / './data/hints/ideas.txt', 'r') as f:
        ideas = f.readlines()
    print(ideas[random.randint(0, len(ideas) - 1)])

@main.command()
def debug():
    with open(SCRIPT_DIR / './data/hints/bugs.txt', 'r') as f:
        bugs = f.readlines()
    print(bugs[random.randint(0, len(bugs) - 1)])


if __name__ == '__main__':
    main()
