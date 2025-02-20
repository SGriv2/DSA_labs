import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# Load the dataset
data = pd.read_csv('zoo.csv')

# Drop non-numeric columns
df = data.drop(['animal_name', 'class_type'], axis=1)

# Convert to float
x = df.values.astype(float)

# Standardize the data
scaler = StandardScaler()
x = scaler.fit_transform(x)

# Apply PCA
pca = PCA(n_components=2)
x = pca.fit_transform(x)

# Apply KMeans clustering
kmeans_model = KMeans(n_clusters=4, init='k-means++', random_state=0)
kmeans_model.fit(x)

# Add cluster labels to the dataframe
df['cluster'] = kmeans_model.labels_

# Display the mean of each feature per cluster
pd.set_option('display.max_columns', None)

# Plot the clusters
clusters = (0, 1, 2, 3)
colors = ('r', 'g', 'b', 'y')


for cl, color in zip(clusters, colors):
    plt.scatter(
        x[df['cluster'] == cl, 0], 
        x[df['cluster'] == cl, 1], 
        s=50, 
        c=color, 
        label='Cluster ' + str(cl)
    )

# Plot the centroids
plt.scatter(
    kmeans_model.cluster_centers_[:, 0], 
    kmeans_model.cluster_centers_[:, 1], 
    s=100, 
    c='black', 
    label='Centroid'
)

# Add plot details
plt.title('K-means Clustering (K=4)')
plt.xlabel('PC1')
plt.ylabel('PC2')
plt.legend()
plt.show()

