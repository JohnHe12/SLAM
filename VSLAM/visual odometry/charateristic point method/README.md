# Charateristic Point Method

## Caluculate the Essential Matrix

### a. 8 point method linear solution

Here is to explain in Eigen or mathmatical, how to calculate the essential matrxi, because of the x_2^T E x1= 0, so we use eight point method,Ae = 0, but if we use eigen to calculate the e, we can just get a vector whose elements is eaqual to zero, and if the point if bigger than the eight point, we can use the least square to estimate the e, so expend the A dim(8,9) to the dim(n,9), n is the number of matched points.use SVD decomposition,
$$
  A=U\Sigma V^T
$$

$$
Ae = 0 ----> argmin ||Ae||
$$

so, we put the SVD in to the function and know the Orthogonal Matrix will not change the Norm of the matrix

$$
min||U\Sigma V^Te|| --> min||\Sigma y||,y=V^Te,||y||=1
$$

because of the $\Sigma$ is the non-negative and from big to small, so $y=(0,0,0,....,1)^T$.

$y=V^Te-->e=V^{-T}y$ beacause V is ortogonal matric, this means $V^{-1}=V^T$ so $e=Vy$. this means e is the last colum of the marix V. And more is V is the eigenvector of $A^TA$.Then we get the e, and transform it to the matrix, we will get the essential matrix **E**. And to calculate the fundamental matrix **F** is the same. $E = K^{-1}FK$. But **F** or **E** generally is not satisfied the constrain that the rank of the matrix is 2. so we need to repair the $\Sigma$

$$
F = U\Sigma V^T---> \Sigma^{prime}=\begin{bmatrix}
\sigma(0)&&\\
&\sigma(1)&\\
&&0\\
\end{bmatrix}--->F^{prime}=U\Sigma^{prime}V^T
$$

Note: The last colum represent the eigenvector which corresponding to the smallest eigenvalue, so in the Eigen is the first col.

### 8 point method normalized coordinate

First we calculate the mean value of the x,y of the matched points.
$$
u_{m} = \frac{1}{N}\sum x_i;
\space v_m = \frac{1}{N} \sum y_i
$$
so then calculate
$$
meanX = \frac{1}{N}\sum |u_i-u_m|\\
\space\\
meanY = \frac{1}{N}\sum |v_i - v_m|
$$
and the last
$$
sX = \frac{1}{meanX}\\
\space\\
sY = \frac{1}{meanY}
$$

so the transfomed point
$$
  x'=(u_i-u_m) * sX\\
  y'=(v_-v_m) * sY
$$

so get the transfromtion matrix
$$
\begin{pmatrix}
  x'\\y'\\1
\end{pmatrix}=\begin{bmatrix}
  sX&0&-u_m*sX\\
  0&sY&-v_m*sY\\
  0&0&1
\end{bmatrix}\begin{pmatrix}
  u\\v\\1
\end{pmatrix}\\
 \space\\
 \\
T = \begin{bmatrix}
  sX&0&-u_m*sX\\
  0&sY&-v_m*sY\\
  0&0&1
\end{bmatrix}
$$

according to the 8 point methode before, the $F'$ cna be calculate carrorfing to the $x_2'^TF'x_1'=0$
and the fundamential matrix we need can be calculate
$$
(T_2x_2)^TF'(T_1x_1)=x_2^TT_2^TF'T_1x_1=0\\
\space \\
F = T_2^TF'T_1
$$

### 7 point method

not finished if i have time

## PnP

So it needs to optimize the pose of the camera, in order to realize the goal, the dervided needs to be calculated.

### Lie group and Lie algebra

before we introduce the PnP, we need to talk about the Lie group and Lie algebra. as we known, the rotation matrix can be multiple but can not add to another rotation matrix,but Lie algebra can represent the rotation matrix, and (-pi,pi), one rotation matrix maps a Lie algebra.

some properties need to be kown:

- $e^{\phi ^\wedge } = R\space$ this is the map rotation matrix and Lie algebra
- $e^{\phi ^\wedge } = \cos \theta I + (1 - \cos \theta)aa^T +\sin \theta a^\wedge , \phi=\theta a,||a||=1$
- BCH make the addition of Lie algebra possible.

$$
\ln(e^{\phi _1 ^\wedge}e^{\phi _2 ^\wedge}) = \begin{cases}
  J_l^{-1}\phi _1 + \phi _2\\
  J_r^{-1}\phi _2 + \phi _1\\
\end{cases}
$$

after that, we can deviter of the rotation.

so now if have a posetion in global coordinate $P$, this point in the camera coordinate is $P'$, so $P' = TP$, and the here p is 4x1 matrix $[X,Y,Z,1]^T,T=\begin{bmatrix}
  R&t\\
  0&1
\end{bmatrix}$,use intrinx parameter, $Z'u = KP'$,now in the image we can obeserve a point $p_2=[u_2,v_2,1]^T$, $e = p_2-KTP$ if we have n-point so the least square can be calculate to minimize the e, subject to the T, we can optimize the T.$arg \min_{T}||p_i-KTP_i||$, so $e-->P'--->P$.

$$
\frac{\partial (Rp)}{\partial \varphi } =\lim_{x \to 0}\frac{e^{\varphi^\wedge}e^{\phi}p-e^{\phi}p }{\varphi}\\
\space\\
=\lim_{x \to 0}\frac{(I + \varphi^\wedge)e^{\phi}p-e^{\phi}p}{\varphi}\\
\space\\
=\lim_{x \to 0}\frac{\varphi^\wedge e^{\phi}p}{\varphi}=\frac{-(Rp)^{\wedge}\varphi}{\varphi}=-(Rp)^{\wedge}
$$

as the same for se(3)
$$
\frac{\partial (Tp)}{\partial \zeta } = \begin{bmatrix}
  I&-(Rp+t)^{\wedge}\\
  0^T&0^T
\end{bmatrix}=(TP)^{\odot}
$$

### Implenment

Now it is time to minimize the error subject to the T, and we need a mid tempelet param $P'$ which represent the camera coordinate

$$
\frac{\partial e}{\partial \zeta} = \frac{\partial e}{\partial P'}\frac{\partial P'}{\partial \zeta}
$$
according to the intrinx parameter $K$, we can calculate relationship between,u and P'.
$$
K = \begin{bmatrix}
  f_x&0&c_x\\
  0&f_y&c_y\\
  0&0&0\\
\end{bmatrix}\\
\space\\
\begin{cases}
  u=f_X\frac{X'}{Z'} + c_X\\
  v=f_y\frac{Y'}{Z'} + c_y
\end{cases}
$$
$$
\frac{\partial e}{\partial P'} = \begin{bmatrix}
  \frac{\partial u}{\partial X'}&\frac{\partial u}{\partial Y'}&\frac{\partial u}{\partial Z'}\\
  \frac{\partial v}{\partial X'}&\frac{\partial v}{\partial Y'}&\frac{\partial v}{\partial Z'}
\end{bmatrix} = \begin{bmatrix}
  \frac{f_x}{Z'}&0&-\frac{f_xX}{Z'^2}\\
  0&\frac{f_x}{Z'}&-\frac{f_xY}{Z'^2}
\end{bmatrix}
$$
$$
\frac{\partial P'}{\partial \zeta} = \frac{\partial (TP)}{\partial \zeta}=(TP)^{\odot}=\begin{bmatrix}
  I&-(Rp+t)^{\wedge}\\
  0^T&0^T
\end{bmatrix}
$$

because we just pick the first there dimension, so
$$\frac{\partial P'}{\partial \zeta}=\begin{bmatrix}
  I&-(Rp+t)^{\wedge}\\
\end{bmatrix}$$

multiple two matrix:
$$
\frac{\partial e}{\partial \zeta} = \frac{\partial e}{\partial P'}\frac{\partial P'}{\partial \zeta}=
\begin{bmatrix}
  \frac{f_x}{Z'}&0&-\frac{f_xX}{Z'^2}\\
  0&\frac{f_x}{Z'}&-\frac{f_xY}{Z'^2}
\end{bmatrix}
\begin{bmatrix}
  I&-(Rp+t)^{\wedge}
\end{bmatrix}
$$

now the T has been optimized, at the same time we can also re-optimize the 3D-point arrording to the $\frac{\partial e}{\partial P}$.
$$
\frac{\partial e}{\partial P}=\frac{\partial e}{\partial P'}\frac{\partial P'}{\partial P}
$$

$$
\frac{\partial P'}{\partial P}= \frac{\partial (RP+t)}{\partial P} = R
$$

so the result is
$$
\frac{\partial e}{\partial P}=\begin{bmatrix}
  \frac{f_x}{Z'}&0&-\frac{f_xX}{Z'^2}\\
  0&\frac{f_x}{Z'}&-\frac{f_xY}{Z'^2}
\end{bmatrix}R
$$
## PLAN

not finished.

plan：

1. 10/5 morning 8 point method

2. afternoon pnp, icp.

3. evening code, begin chapter 8.
