#!/usr/bin/python

import argparse
from tempfile import NamedTemporaryFile
import csv
import shutil

parser = argparse.ArgumentParser( description='Translate a CSV file that uses id numbers for a column into literal values. Please note that this is destructive and modifies the origial data file.')
parser.add_argument('data_filename', type=str, help='the name/path of the CSV with the data')
parser.add_argument('translation_filename', type=str, help='the name/path of the CSV with the translations')
args = parser.parse_args()

data_filename=args.data_filename
translation_filename=args.translation_filename

tempfile = NamedTemporaryFile(mode='w', delete=False)

with open(data_filename, 'r') as data_file, open(translation_filename, 'r') as translation_file, tempfile:
    values = csv.DictReader(data_file)
    translations = csv.DictReader(translation_file)

    # prep written file
    writer = csv.DictWriter(tempfile,fieldnames = values.fieldnames)
    writer.writeheader()

    for bench_entry in values:
        for translation in translations:

            trans_key = translation["key"]
            if trans_key in bench_entry:
                if bench_entry[trans_key] == translation['from']:
                    bench_entry[trans_key] = translation['to']
        writer.writerow(bench_entry)
        translation_file.seek(0)
shutil.move(tempfile.name, data_filename)
