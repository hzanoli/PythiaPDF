#!/usr/bin/env python3

import subprocess
import argparse
import ROOT

parser = argparse.ArgumentParser(description='Obtain multiple PDFs')

parser.add_argument('--momentum_transfer', '-q2', type=float, nargs='+',
                    help='List of q2 values to be plotted',
                    default=[1, 1.4, 4, 10, 100, 1000])

parser.add_argument('--pdf_name', '-p', nargs='+', type=str,
                    help='List of pdf names to be plotted',
                    default=['Default'] + [f'CT14nnloIC/{id}' for id in range(6)])

args = parser.parse_args()
print()
print(args.pdf_name)
print(args.momentum_transfer)

for pdf_name in args.pdf_name:
    for momentum_transfer in args.momentum_transfer:
        subprocess.run(['pythiapdf', '--pdf_name', str(pdf_name), 
                    '--momentum_transfer', str(momentum_transfer)])

results = [f"PDF_{pdf_name}_Q2_{momentum_transfer}.root" 
           for pdf_name in args.pdf_name
           for momentum_transfer in args.momentum_transfer]

merged_results = ROOT.TFile("merged.root", "RECREATE")

for file_name in results:
    file = ROOT.TFile(file_name)
    folder_name = file_name[:-5]
    histograms = [file.Get(a.GetName()) for a in file.GetListOfKeys()]

    merged_results.cd()
    for hist in histograms:
        hist.Write(f"{folder_name}/{hist.GetName()}")
    

print(merged_results.ls())
