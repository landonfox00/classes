
import pandas as pd
import matplotlib.pyplot as plt
import sklearn as skl
# !pip install scikit-optimize

df = pd.read_csv( 'solar.csv' )

vars = [ 'VAR78', 'VAR79', 'VAR134', 'VAR157', 'VAR164', 'VAR165', 'VAR166', 'VAR167', 'VAR169', 'VAR175', 'VAR178', 'VAR228' ]
df[ vars ] = ( df[ vars ] - df[ vars ].mean() ) / df[ vars ].std()
# df[vars] =(df[vars]-df[vars].min())/(df[vars].max()-df[vars].min()) # no good

df1 = df[ df['ZONEID'] == 1 ]
split1 = df1.loc[ df1.isin( [ '20130701 01:00' ] ).any( axis=1 ) ].index.tolist()[ 0 ]
df1_train = df1[ :split1 ]
df1_test = df1[ split1: ]

df2 = df[ df['ZONEID'] == 2 ]
split2 = df2.loc[ df2.isin( [ '20130701 01:00' ] ).any( axis=1 ) ].index.tolist()[ 0 ]
df2_train = df2[ :split2 ]
df2_test = df2[ split2: ]

df3 = df[ df['ZONEID'] == 3 ]
split3 = df3.loc[ df3.isin( [ '20130701 01:00' ] ).any( axis=1 ) ].index.tolist()[ 0 ]
df3_train = df3[ :split3 ]
df3_test = df3[ split3: ]

from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.ensemble import GradientBoostingRegressor

# parameters = {'learning_rate': [0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16],
#                   'subsample'    : [0.9, 0.5, 0.2, 0.1],
#                   'n_estimators' : [100,500,1000, 1500],
#                   'max_depth'    : [4,6,8,10]
#              }
GBR = GradientBoostingRegressor( random_state=1, verbose=1,  )
# grid_GBR = GridSearchCV(estimator=GBR, param_grid = parameters, cv = 2, n_jobs=-1)

from sklearn.model_selection import RandomizedSearchCV
from scipy.stats import uniform as sp_randFloat
from scipy.stats import randint as sp_randInt

score = 0
while score < 0.8:
# model = GradientBoostingRegressor()
	parameters = {'learning_rate': sp_randFloat(),
	              'subsample'    : sp_randFloat(),
	              'n_estimators' : sp_randInt(100, 1000),
	              'max_depth'    : sp_randInt(4, 10) 
	             }

	grid_GBR = RandomizedSearchCV(estimator=GBR, param_distributions = parameters, 
	                           cv = 2, n_iter = 10, n_jobs=-1)
	grid_GBR.fit(df1_train[ vars ][ :-24 ], df1_train['POWER'][ 24: ])

	# grid_GBR.fit(df1_train[ vars ][ :-24 ], df1_train['POWER'][ 24: ] )
	print(" Results from Grid Search " )
	print("\n The best estimator across ALL searched params:\n",grid_GBR.best_estimator_)
	print("\n The best score across ALL searched params:\n",grid_GBR.best_score_)
	print("\n The best parameters across ALL searched params:\n",grid_GBR.best_params_)
	score = grid_GBR.best_score_