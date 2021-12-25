import click
import filecmp
import glob
import logging
import pathlib
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

@main.command()
@click.option('--data-dir', required=True)
@click.option('--binary', required=True)
@click.option('--output-dir', default='./tmp')
@click.option('--input-suffix', default='.in')
@click.option('--output-suffix', default='.out')
def from_data(data_dir, binary, output_dir, input_suffix, output_suffix):
    pathlib.Path(output_dir).mkdir(exist_ok=True)
    problematic_list = []
    for input_file in glob.glob(data_dir + "/*" + input_suffix):
        logging.info('Processing {}'.format(input_file))
        ok = True
        with open(input_file, 'r') as f:
            expected_output_file = pathlib.PurePath(data_dir, pathlib.PurePath(input_file).stem + output_suffix)
            output_file = pathlib.PurePath(output_dir, pathlib.PurePath(input_file).stem + output_suffix)
            try:
                with open(output_file, 'w') as g:
                    subprocess.run(binary, stdin=f, stdout=g, check=True)
                if not filecmp.cmp(expected_output_file, output_file):
                    logging.error('Difference catched when processing {}.'.format(input_file))
                    ok = False
            except:
                logging.error('Processing {} fail, just skip'.format(input_file))
                ok = False
        if ok == False:
            problematic_list.append(input_file)
    if (len(problematic_list) > 0):
        logging.error("problematic_list: {}".format(problematic_list))
        for input_file in problematic_list:
            logging.error("{}: file_size={}".format(input_file, pathlib.Path(input_file).stat().st_size))


if __name__ == '__main__':
    main()
