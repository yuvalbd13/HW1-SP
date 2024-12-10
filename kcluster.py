import math;








def euclidian_distance(arr):
     j=len(arr)
     sum=0
     dis=0.0
     for i in range(j):
          sum=sum+arr[i]
     dis=math.sqrt(sum)
     return dis



def minimal_distance(arr):
     #we get as an input the array of lists(?) and we always save the minimal distance
     p=len(arr)
     curr_dis=-1
     dis_min=-1
     for i in range(p):
          if(curr_dis==-1):
               curr_dis=euclidian_distance(arr[i])
               dis_min=curr_dis
          else:
               curr_dis=euclidian_distance(arr[i])
               if(dis_min>curr_dis):
                    dis_min=curr_dis



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

#we need to make a function that assigns x_i to the cluster with the minimal distance















