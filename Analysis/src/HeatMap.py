from Analysis import *
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import colors, ticker
import matplotlib.cm as cm

#==========================
# PARAMETERS
#==========================
Namefile="Equatorial_coordinates_final.dat"

#==========================
# LOADING FILES
#==========================
filename=AnalDir + Namefile 
Alpha,Delta=np.loadtxt(filename,unpack=True)

#=========================
# SOME SHORCUTS
#=========================
Max=np.max
Min=np.min
Ceil=np.ceil
Floor=np.floor

#==========================
# STABLISHING LIMITS
#==========================
Amax=Max(Ceil(Alpha))
Amin=Min(Floor(Alpha))
Dmax=Max(Ceil(Delta))
Dmin=Min(Floor(Delta))

dA=(Amax-Amin)/20.0
dD=(Dmax-Dmin)/20.0

#A=np.arange(Amin,Amax+dA,dA)
#D=np.arange(Dmin,Dmax+dD,dD)
A=np.linspace(Amin,Amax,20)
D=np.linspace(Dmin,Dmax,20)
X,Y=np.meshgrid(A,D)

Z=np.zeros_like(X)

for i in range(len(D)-1):
    for j in range(len(A)-1):
        for k in range(len(Alpha)):
            #print "i:%d    j:%d    k:%d   Z[%d][%d]= %d\n"%(i,j,k,j,i,Z[j][i])
            if Alpha[k]<=A[j+1] and Alpha[k]>=A[j]:
                if Delta[k]<=D[i+1] and Delta[k]>=D[i]:
                    Z[j][i]=Z[j][i]+1
                    #print "i:%d    j:%d    k:%d   Z[%d][%d]= %d\n"%(i,j,k,j,i,Z[j][i])

fig1=plt.figure()
Smth=fig1.add_subplot(111)
#cs1=plt.contourf(X,Y,Z,cmap=cm.gray)
#cs1=plt.contourf(X,Y,Z,cmap=cm.hot,alpha=0.9)
im=Smth.imshow(Z/Z.sum()*100, interpolation='bilinear', cmap=cm.bone,origin='lower', extent=[Amin,Amax,Dmin,Dmax],aspect='auto')
CS = plt.contour(X, Y, Z/Z.sum()*100,colors='y',linewidth=0.5,linestyles='dashed',)
plt.clabel(CS, fontsize=9, inline=2,fmt="%.1f")
#plt.colorbar(im,orientation='horizontal',shrink=0.8)
plt.colorbar(im)
plt.grid(True,color='y',linestyle='--')

fig2=plt.figure()
Ctr=fig2.add_subplot(111)
cs1=Ctr.contourf(X,Y,Z,cmap=cm.hot,alpha=0.9)
CS = Ctr.contour(X, Y, Z,colors='k',linewidth=0.5,linestyles='dashed',)
Ctr.clabel(CS, fontsize=9, inline=2,fmt="%.1f")
plt.colorbar(cs1,format="%.2lf")
Ctr.set_xlim([Amin,Amax])
Ctr.set_ylim([Dmin,Dmax])
Ctr.grid(True,color='y',ls='--')


plt.show()
