import math
import sys








def euclidian_distance(arr1,arr2):
     #calculates the euclidian distance between two vectors(arrays in this implementation)
     j=len(arr1)
     sum=0
     dis=0.0
     for i in range(j):
          sum=sum+abs(arr1[i]-arr2[i])
     dis=math.sqrt(sum)
     return dis



def minimal_distance(arr,vector):
     #we get as an input the array of lists(?) and we always save the minimal distance
     p=len(arr)
     curr_dis=-1
     dis_min=-1
     for i in range(p):
          if(curr_dis==-1):
               curr_dis=euclidian_distance(arr[i],vector)
               dis_min=curr_dis
          else:
               curr_dis=euclidian_distance(arr[i],vector)
               if(dis_min>curr_dis):
                    dis_min=curr_dis
     return dis_min



def calculate_mewk(arr,n):
     #we calculate the value with the formula given in the algorithm in stage 4
     #len(arr) will be our k in the formula
     #n is the size of each vector in this context
     sum=0.0
     k=len(arr)
     vectoravg=[]
     for i in range(n):
          vectoravg.append(0.0)
     for i in range(k):
          for p in range(n):
               vectoravg[p]=vectoravg[p]+arr[i][p]
     for d in range(n):
          vectoravg[d]=vectoravg[d]/k
     return vectoravg

def read_all_lines(file_name):
     vectorarr=[]
     with open(file_name) as f:
          lines=f.readlines()
          for line in lines:
               curr_vector=line.split()
               for i in range(len(curr_vector)):
                    curr_vector[i]=float(curr_vector[i])
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
     file_name=input("Enter file name: ")
     vecarr=read_all_lines(file_name)
     #now we will create the clustering arrays needed,it will be a list of lists
     k=input("Enter number of clusters: ")
     clusters=set_clusters(vecarr,k)
     list_of_clusters=[]
     for i in range(k):
          list_of_clusters.append(clusters[i])
     for i in range(k,len(vecarr)):#bc the clusters will also be in assignment to themselves
          j=minimal_distance(clusters,vecarr[i])
          list_of_clusters[j].append(vecarr[i])
     #now we have a list of the assigments of the clusters, we are ready to recalculate and reapeat the algorithm.
####the newest



























