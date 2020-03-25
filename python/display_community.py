# =================
# ==== Imports ====
# =================

import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import networkx as nx


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
	ax_lab = sns.heatmap(result_label, vmin=1, vmax=10, center=4, cmap="YlGnBu")

	result_louvain = df[df["method"] == 'Louvain'].pivot(index="p", columns="q", values="number_community")
	fig_lou, ax_lou = plt.subplots()
	ax_lou = sns.heatmap(result_louvain, vmin=1, vmax=10, center=4, cmap="YlGnBu")
	plt.show()

def compute_coverage(graph_file, partition_file, zero=False):
	intify = lambda L: [int(l) for l in L]
	edges = [intify(l.replace("\n", "").split("\t")) for l in open(graph_file).readlines()]
	max_node = edges[-1][1]+1

	# Lecture du graphe
	print("Lecture du graphe ...")
	G = nx.Graph()
	G.add_nodes_from(range(max_node))
	G.add_edges_from(edges)

	# construction de la partition
	print("Construction des partitions ...")
	partition = []
	c2partition = {}
	communities = [intify(l.replace("\n", "").split("\t")) for l in open(partition_file).readlines()]
	for i in range(len(communities)):
		if communities[i][1] not in c2partition:
			c2partition[communities[i][1]] = len(partition)
			partition.append({communities[i][0]})
		else:
			partition[c2partition[communities[i][1]]].add(communities[i][0])
	if zero:
		partition.append({0})

	print("\tNb partitions:", len(partition))

	print("\tCoverage:",nx.algorithms.community.quality.coverage(G, partition))



# =============
# ==== RUN ====
# =============

if __name__ == '__main__':

	INPUT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "results", "interm", "community_detection.csv")
	print(INPUT_FILE)
	display_community(input_file=INPUT_FILE)
	INPUT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "instances", "LFR_graph")
	LABEL_RESULT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "results", "label_LFR_graph")
	LOUVAIN_RESULT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "results", "louvain_LFR_graph")

	for p in ["_1000.nse", "_5000.nse", "_10000.nse", "_50000.nse"]:
		print("\n",p)
		compute_coverage(INPUT_FILE+p, INPUT_FILE+p[:-4]+".nmc", zero=True)
		compute_coverage(INPUT_FILE+p, LABEL_RESULT_FILE+p)
		compute_coverage(INPUT_FILE+p, LOUVAIN_RESULT_FILE+p)