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
	plt.figure(num=1)
	sns.relplot(x="q", y="number_community",
				hue="method",
				#size="p", size_norm=(),
				palette="muted",
				col="method",
				data=df)
	plt.show()
	plt.close(1)


# =============
# ==== RUN ====
# =============

if __name__ == '__main__':

	INPUT_FILE = os.path.join(os.path.dirname(__file__), os.pardir, "results", "interm", "community_detection.csv")
	print(INPUT_FILE)
	display_community(input_file=INPUT_FILE)