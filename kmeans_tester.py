import numpy as np
import time
from copy import deepcopy

def generate_data(num_points, num_features, num_clusters, spread=1.0):
    """
    Generate synthetic data for K-Means testing.

    :param num_points: Total number of points to generate.
    :param num_features: Dimensionality of the data.
    :param num_clusters: Number of clusters to generate.
    :param spread: Standard deviation of clusters.
    :return: numpy array of generated data.
    """
    centers = np.random.rand(num_clusters, num_features) * 10
    data = []
    for i in range(num_clusters):
        points = np.random.randn(num_points // num_clusters, num_features) * spread + centers[i]
        data.extend(points)
    np.random.shuffle(data)
    return np.array(data)

def write_to_file(data, file_name):
    """
    Write a dataset to a file in the format expected by the K-Means implementation.

    :param data: numpy array of data to write.
    :param file_name: Name of the file to write to.
    """
    with open(file_name, 'w') as f:
        for point in data:
            f.write(",".join(map(str, point)) + "\n")

def test_kmeans():
    """
    Test the K-Means implementation with various datasets.
    """
    from kmeans import main  # Import your K-Means algorithm's main function

    # Define test configurations
    test_cases = [
        {"num_points": 100, "num_features": 2, "num_clusters": 3},
        {"num_points": 500, "num_features": 5, "num_clusters": 5},
        {"num_points": 1000, "num_features": 3, "num_clusters": 4},
        {"num_points": 200, "num_features": 10, "num_clusters": 8},
    ]

    for idx, config in enumerate(test_cases):
        print(f"Running test case {idx + 1}: {config}")

        # Generate synthetic data
        data = generate_data(
            num_points=config["num_points"],
            num_features=config["num_features"],
            num_clusters=config["num_clusters"],
            spread=1.0
        )

        # Write data to file
        file_name = f"test_case_{idx + 1}.txt"
        write_to_file(data, file_name)

        # Run K-Means
        k = config["num_clusters"]
        iter_max = 200

        start_time = time.time()
        try:
            main_args = ["script_name", str(k), str(iter_max), file_name]
            sys.argv = main_args  # Mock command-line arguments
            main()
            print(f"Test case {idx + 1} completed successfully in {time.time() - start_time:.2f} seconds.")
        except Exception as e:
            print(f"Test case {idx + 1} failed: {e}")

if __name__ == "__main__":
    test_kmeans()
