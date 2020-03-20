# =================
# ==== Imports ====
# =================

import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
import os


# ===================
# ==== Functions ====
# ===================

def display_kcore(file_name):
	"""
	"""

	df = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(file_name, "r").readlines()]).astype('int')
	df.rename(columns={0:"index", 1:"coreness", 2:"degree"}, inplace=True)
	df = df[df["index"]>0]
	df = df[df["coreness"]>0]
	df["occurancy"] = pd.Series([1 for i in range(len(df))])
	df = df.groupby(by=["coreness", "degree"], as_index=False).agg({"occurancy":sum})
	#df["occurancy"] = df["occurancy"].apply(lambda x: pd.np.log(x))

	fig, ax = plt.subplots(figsize=(8, 9))
	scat = ax.scatter(pd.np.log(df["degree"].values), pd.np.log(df["coreness"].values), c=df["occurancy"].values, 
		cmap='jet', label="coreness", norm=matplotlib.colors.LogNorm())
	axes = plt.gca()
	x = [0,max(axes.get_ylim()[1], axes.get_xlim()[1])]
	ax.plot(x, x, '--', label="Identity line")
	ax.grid()
	#ax.xlabel("$\log(Degree)$")
	#ax.ylabel("$\log(Coreness)$")

	ax.legend(loc='upper left', scatterpoints=1)
	ax.set(xlabel='Degree', ylabel='Coreness')
	cbar = fig.colorbar(scat, orientation='horizontal')
	cbar.set_label('Occurancy')
	cbar.formatter.useOffset = False
	cbar.update_ticks()
	fig.tight_layout()

	plt.show()


# =============
# ==== RUN ====
# =============

if __name__ == '__main__':

	FILE = "kcore_net.txt"
	#FILE = "kcore_email-Eu-core-clean.txt"
	#FILE = kcore_com-amazon.ungraph-clean.txt"
	NAME = os.path.join(os.path.dirname(__file__), os.pardir, "results", FILE)
	display_kcore(file_name=NAME)