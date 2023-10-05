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

## PLAN

not finished.

plan：

1. 10/5 morning 8 point method

2. afternoon pnp, icp.

3. evening code, begin chapter 8.
