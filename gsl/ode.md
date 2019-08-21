# ODE

Solve an ordinary differential equation and output the solution to stdout:

    ./ode.out

Source: [ode.c](ode.c)

Plot with gnuplot:

    ./ode.out > ode.dat
    ./ode.gnuplot
    xdg-open ode.png

Output:

![](https://raw.githubusercontent.com/cirosantilli/media/master/ode.png)

To also plot the phase space on a plplot output window use an argument:

    ./ode.out 1

An ODE of any order can be reduced to a system of first order ODEs: therefore, GSL only offers an API to solve systems of first order ODEs.

In this particular example we, solve the second order autonomous https://en.wikipedia.org/wiki/Van_der_Pol_oscillator ODE equation:

    g : R -> R
    g''(t) = k * g'(t) * (1 - g(t)^2) - g(t) = f(g(t), g'(t), t)

which is equivalent to solving the first order system with two functions y_0 and y_1:

    y_0'(t) = y_1(t)
    y_1'(t) = y_1(t) * (1 - y_0(t)^2) - y_0(t)

with:

    y_0(t) = g(t)
    y_1(t) = g'(t)

This function was chosen because it quickly converges to a limit cycle, which is fun to watch.
