# =================
# ==== Imports ====
# =================

import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


# ===================
# ==== Functions ====
# ===================

def display_community(input_file):
	""" Display the results for the different algorithms for community detection
	"""

	df = pd.read_csv(input_file, float_precision='round_trip')
	df['p_divided_by_q'] = df['p']/df['q']
	sns.relplot(x="q", y="number_community",
				hue="p",
				size="running_time", #size_norm=(),
				palette="muted",
				col="method",
				data=df)
	sns.relplot(x="p_divided_by_q", y="number_community",
				hue="method",
				size="running_time", #size_norm=(),
				palette="muted",
				col="method",
				data=df)
	
	# Heatmap
	result_label = df[df["method"] == 'Label'].pivot(index="p", columns="q", values="number_community")
	fig_lab, ax_lab = plt.subplots()
	ax_lab = sns.heatmap(result_label)

	result_louvain = df[df["method"] == 'Louvain'].pivot(index="p", columns="q", values="number_community")
	fig_lou, ax_lou = plt.subplots()
	ax_lou = sns.heatmap(result_louvain)
	plt.show()


# =============
# ==== RUN ====
# =============

if __name__ == '__main__':

	INPUT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "results", "interm", "community_detection.csv")
	print(INPUT_FILE)
	display_community(input_file=INPUT_FILE)