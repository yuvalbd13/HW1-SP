import math
import sys
from copy import deepcopy


def euclidian_distance(arr1,arr2):
     #calculates the euclidian distance between two vectors(arrays in this implementation)
     j = len(arr1)
     sum = 0
     dis = 0.0
     for i in range(j):
          sum = sum + pow(arr1[i]-arr2[i] , 2)
     dis = math.sqrt(sum)
     return dis



def minimal_distance(arr , vector):
     #we get as an input the array of lists(?) and we always save the minimal distance
     p = len(arr)
     curr_dis = 0
     dis_min = euclidian_distance(arr[0] , vector)
     answer_cluster = 0
     for i in range(p):
          curr_dis = euclidian_distance(arr[i] , vector)
          if(dis_min > curr_dis):
               dis_min = curr_dis
               answer_cluster = i
     return answer_cluster



def calculate_mewk(cluster_group):
     #we calculate the value with the formula given in the algorithm in stage 4
     #len(arr) will be our k in the formula
     #n is the size of each vector in this context
     sum = 0.0
     k = len(cluster_group)
     n = len(cluster_group[0])
     vectoravg = []
     for i in range(n):
          vectoravg.append(0.0)
     for i in range(k):
          for p in range(n):
               vectoravg[p] = vectoravg[p] + cluster_group[i][p]
     for d in range(n):
          vectoravg[d]  = vectoravg[d] / k
     return vectoravg

def read_all_lines(file_name):
     vectorarr = []
     with open(file_name) as f:
          lines = f.readlines()
          for line in lines:
               curr_vector = line.split(",")
               for i in range(len(curr_vector)):
                    curr_vector[i] = float(curr_vector[i])
               vectorarr.append(curr_vector)
     return vectorarr

             #i used a generator,mi amar shemavo murhav lo hashuv!





#we need to make a function that assigns x_i to the cluster with the minimal distance
def set_clusters(arr,k):
     #first we set the clusters then we repeat the algorithm
     clusterarr=[]
     for i in range(k):
          clusterarr.append(arr[i])
     return clusterarr


def main():
     iter_max = 200
     if(len(sys.argv) == 4):
          file_name = sys.argv[3]
          iter_max = int(sys.argv[2])
     else:
          file_name = sys.argv[2]
     k = int(sys.argv[1])
     assert(file_name[len(file_name)-4 : len(file_name)] == ".txt")
     vecarr = read_all_lines(file_name)
     assert(1 < k and k < len(vecarr)), "Invalid number of clusters!"
     assert(1 < iter_max and iter_max < 1000), "Invalid maximum iteration!"
     #now we will create the clustering arrays needed,it will be a list of lists
     clusters = set_clusters(vecarr,k)
     eps = 0.002
     iter_count = 0
     while(eps > 0.001 and (iter_count < iter_max)):
          list_of_clusters = []
          for i in range(k):
               list_of_clusters.append([])
          for i in range(len(vecarr)):#bc the clusters will also be in assignment to themselves
               j = minimal_distance(clusters,vecarr[i])
               list_of_clusters[j].append(vecarr[i])
          old_cen = deepcopy(clusters)
          for i in range(len(clusters)):
               clusters[i] = calculate_mewk(list_of_clusters[i])
          a = [0 for i in range(len(clusters))]
          for j in range(len(clusters)):
               a[j] = euclidian_distance(clusters[j],old_cen[j])
          eps = max(a)
          iter_count += 1
     for i in range(len(clusters)):
          for j in range(len(clusters[i])):
               clusters[i][j] = round(clusters[i][j], 4)
     print(clusters)


     #now we have a list of the assigments of the clusters, we are ready to recalculate and reapeat the algorithm.
####the newest

main()
























