import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
import os

graph = 3

if graph ==1:
	NAME =  os.path.join(os.path.dirname(__file__), os.pardir, "results", "pk_alpha=0.15_alr21-dirLinks.txt")
	df = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(NAME, "r").readlines()]).astype('float32')
	df = df[df[1]>0.0001] # sinon le plot galère
	plt.scatter(pd.np.log(df.iloc[:,1].values), pd.np.log(df.iloc[:,2].values))
	plt.grid()
	plt.xlabel("log(Page Rank)")
	plt.ylabel("log(Out Degree)")
	plt.show()

elif graph == 2:
	NAME =  os.path.join(os.path.dirname(__file__), os.pardir, "results", "pk_alpha=0.15_alr21-dirLinks.txt")
	df = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(NAME, "r").readlines()]).astype('float32')
	df = df[df[1]>0.0001] # sinon le plot galère
	plt.scatter(pd.np.log(df.iloc[:,1].values), pd.np.log(df.iloc[:,3].values))
	plt.grid()
	plt.xlabel("log(Page Rank)")
	plt.ylabel("log(Out Degree)")
	plt.show()

elif graph == 3:
	NAME1 =  os.path.join(os.path.dirname(__file__), os.pardir, "results", "pk_alpha=0.15_alr21-dirLinks.txt")
	df1 = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(NAME1, "r").readlines()]).astype('float32')
	df1.rename(columns={0:"index", 1:"rank_1", 2:"inD_1", 3:"outD_1"}, inplace=True)
	df1 = df1[df1["rank_1"]>0.0001] # sinon le plot galère
	df1.drop(columns=["inD_1", "outD_1"], inplace=True)
	
	NAME2 =  os.path.join(os.path.dirname(__file__), os.pardir, "results", "pk_alpha=0.9_alr21-dirLinks.txt")
	df2 = pd.DataFrame([l.replace("\n", "").split("\t") for l in open(NAME2, "r").readlines()]).astype('float32')
	df2.rename(columns={0:"index", 1:"rank_2", 2:"inD_2", 3:"outD_2"}, inplace=True)
	df2 = df2[df2["rank_2"]>0.0001] # sinon le plot galère
	df2.drop(columns=["inD_2", "outD_2"], inplace=True)

	merge_df = pd.merge(df1, df2, on=["index"])
	print(merge_df)
	plt.scatter(merge_df["rank_1"].values, merge_df["rank_2"].values)
	plt.grid()
	plt.xlabel("log(Page Rank) (alpha=0.15)")
	plt.ylabel("log(Page Rank) (alpha=0.9)")
	plt.show()