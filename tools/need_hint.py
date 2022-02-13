import click
import logging
import pathlib
import random

@click.group()
def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

@main.command()
def idea():
    with open('./data/hints/ideas.txt', 'r') as f:
        ideas = f.readlines()
    print(ideas[random.randint(0, len(ideas) - 1)])

@main.command()
def debug():
    with open('./data/hints/bugs.txt', 'r') as f:
        bugs = f.readlines()
    print(bugs[random.randint(0, len(bugs) - 1)])


if __name__ == '__main__':
    main()
