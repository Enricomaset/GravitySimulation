# Mathematical Model of the N-Body Simulation

## 1. Position and velocity

The motion of each body takes place in two dimensions. The position of body $\(i\)$ is

$$
\mathbf r_i=(x_i,y_i),
$$

while its velocity and acceleration are

$$
\mathbf v_i=(v_{x,i},v_{y,i}),
\qquad
\mathbf a_i=(a_{x,i},a_{y,i}).
$$

## 2. Distance between two bodies

Consider two bodies, \(i\) and \(j\), with positions

$$
\mathbf r_i=(x_i,y_i),
\qquad
\mathbf r_j=(x_j,y_j).
$$

The displacement from body \(i\) to body \(j\) is

$$
\Delta x=x_j-x_i,
\qquad
\Delta y=y_j-y_i.
$$

Therefore,

$$
\mathbf r_{ij}
=\mathbf r_j-\mathbf r_i
=(x_j-x_i,\,y_j-y_i).
$$

The distance between the two bodies is

$$
r_{ij}
=\sqrt{(\Delta x)^2+(\Delta y)^2}
=\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}.
$$

## 3. Newton's law of universal gravitation

The magnitude of the gravitational force between bodies \(i\) and \(j\) is

$$
F_{ij}=G\frac{m_i m_j}{r_{ij}^2},
$$

where \(G\) is the gravitational constant.

The force acting on body \(i\) points from body \(i\) toward body \(j\). The unit vector in this direction is

$$
\widehat{\mathbf r}_{ij}
=\frac{\mathbf r_{ij}}{r_{ij}}
=\left(
\frac{x_j-x_i}{r_{ij}},
\frac{y_j-y_i}{r_{ij}}
\right).
$$

The force vector acting on body \(i\) due to body \(j\) is therefore

$$
\mathbf F_{ij}
=F_{ij}\widehat{\mathbf r}_{ij}.
$$

Substituting the previous formulas gives

$$
\mathbf F_{ij}
=G\frac{m_i m_j}{r_{ij}^2}
\frac{\mathbf r_j-\mathbf r_i}{r_{ij}}
=Gm_i m_j
\frac{\mathbf r_j-\mathbf r_i}{r_{ij}^3}.
$$

The power \(r_{ij}^3\) appears because the magnitude of the force contains \(1/r_{ij}^2\), while the unit vector introduces another factor \(1/r_{ij}\).

## 4. Acceleration of one body

Newton's second law is

$$
\mathbf F_i=m_i\mathbf a_i.
$$

Thus, the acceleration of body \(i\) produced by body \(j\) is

$$
\mathbf a_{ij}
=\frac{\mathbf F_{ij}}{m_i}
=Gm_j\frac{\mathbf r_j-\mathbf r_i}{r_{ij}^3}.
$$

The mass \(m_i\) cancels out. The acceleration of body \(i\) therefore depends on the mass \(m_j\) of the body producing the gravitational force.

The two components of the acceleration are

$$
a_{x,ij}
=Gm_j\frac{x_j-x_i}{r_{ij}^3},
$$

$$
a_{y,ij}
=Gm_j\frac{y_j-y_i}{r_{ij}^3}.
$$

Since

$$
r_{ij}^3
=\left(\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}\right)^3,
$$

we obtain

$$
a_{x,ij}
=Gm_j
\frac{x_j-x_i}
{\left(\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}\right)^3},
$$

$$
a_{y,ij}
=Gm_j
\frac{y_j-y_i}
{\left(\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}\right)^3}.
$$

## 5. Extension to \(N\) bodies

In a system containing \(N\) bodies, body \(i\) is attracted by every other body. Its total acceleration is obtained by adding all the individual contributions.

For the horizontal component,

$$
a_{x,i}
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{x_j-x_i}{r_{ij}^3}.
$$

For the vertical component,

$$
a_{y,i}
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{y_j-y_i}{r_{ij}^3}.
$$

Here,

$$
r_{ij}=\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}.
$$

The condition \(j\ne i\) excludes the body itself from the sum. Otherwise, \(r_{ii}=0\), which would cause a division by zero.

In vector form,

$$
\mathbf a_i
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{\mathbf r_j-\mathbf r_i}{r_{ij}^3}.
$$

## 6. Discretization of time

The continuous motion is approximated at discrete instants. Let

$$
t_{n+1}=t_n+\Delta t,
$$

where \(\Delta t\) is the time step.

At time \(t_n\), body \(i\) has position, velocity and acceleration

$$
(x_i^n,y_i^n),
\qquad
(v_{x,i}^n,v_{y,i}^n),
\qquad
(a_{x,i}^n,a_{y,i}^n).
$$

## 7. Velocity update

Acceleration is the derivative of velocity:

$$
\mathbf a=\frac{d\mathbf v}{dt}.
$$

Using a forward finite difference,

$$
\mathbf a_i^n
\approx
\frac{\mathbf v_i^{n+1}-\mathbf v_i^n}{\Delta t}.
$$

Therefore,

$$
\mathbf v_i^{n+1}
=\mathbf v_i^n+\mathbf a_i^n\Delta t.
$$

In components,

$$
v_{x,i}^{n+1}
=v_{x,i}^n+a_{x,i}^n\Delta t,
$$

$$
v_{y,i}^{n+1}
=v_{y,i}^n+a_{y,i}^n\Delta t.
$$

## 8. Position update

Velocity is the derivative of position:

$$
\mathbf v=\frac{d\mathbf r}{dt}.
$$

Using a forward finite difference,

$$
\mathbf v_i^n
\approx
\frac{\mathbf r_i^{n+1}-\mathbf r_i^n}{\Delta t}.
$$

Therefore,

$$
\mathbf r_i^{n+1}
=\mathbf r_i^n+\mathbf v_i^n\Delta t.
$$

In components,

$$
x_i^{n+1}
=x_i^n+v_{x,i}^n\Delta t,
$$

$$
y_i^{n+1}
=y_i^n+v_{y,i}^n\Delta t.
$$

Thus, at each time step, the calculation follows this order:

$$
(x_i^n,y_i^n)
\longrightarrow
(a_{x,i}^n,a_{y,i}^n)
\longrightarrow
(v_{x,i}^{n+1},v_{y,i}^{n+1})
\longrightarrow
(x_i^{n+1},y_i^{n+1}).
$$

The position formula uses the velocity at time \(t_n\), exactly as in the calculations above.

## 9. Final equations

For every body \(i\), the acceleration at time \(t_n\) is

$$
\boxed{
a_{x,i}^n
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{x_j^n-x_i^n}{(r_{ij}^n)^3}
}
$$

and

$$
\boxed{
a_{y,i}^n
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{y_j^n-y_i^n}{(r_{ij}^n)^3}
}
$$

with

$$
r_{ij}^n
=\sqrt{(x_j^n-x_i^n)^2+(y_j^n-y_i^n)^2}.
$$

The velocity is updated using

$$
\boxed{
v_{x,i}^{n+1}
=v_{x,i}^n+a_{x,i}^n\Delta t
}
$$

and

$$
\boxed{
v_{y,i}^{n+1}
=v_{y,i}^n+a_{y,i}^n\Delta t
}.
$$

Finally, the position is updated using

$$
\boxed{
x_i^{n+1}
=x_i^n+v_{x,i}^n\Delta t
}
$$

and

$$
\boxed{
y_i^{n+1}
=y_i^n+v_{y,i}^n\Delta t
}.
$$

These equations form the mathematical core of the two-dimensional N-body simulation.
