# Interior Control of the Poisson Equation with the Steepest Descent Method in OpenFOAM

In this work we solve the optimal control problem

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5Cmin%20_%7Bu%20%5Cin%20L%5E2%20%5Cleft%28%20%5COmega%20%5Cright%29%7D%20%5Cmathcal%7BJ%7D%5Cleft%28%20u%5Cright%29%20%3D%20%5Cmin%20_%7Bu%20%5Cin%20L%5E2%20%5Cleft%28%20%5COmega%20%5Cright%29%7D%20%5Cfrac%7B1%7D%7B2%7D%20%5Cint_%7B%5COmega%7D%20%5Cleft%28%20y%20-%20y_d%20%5Cright%29%20%5E2%20%5Cmathrm%7Bd%7D%20%5COmega%20&plus;%20%5Cfrac%7B%5Cbeta%7D%7B2%7D%20%5Cint_%7B%5COmega%7D%20u%20%5E2%20%5Cmathrm%7Bd%7D%20%5COmega%2C">
</p>

where <img src="https://latex.codecogs.com/gif.latex?u"> is the control variable, <img src="https://latex.codecogs.com/gif.latex?u"> the state variable and <img src="https://latex.codecogs.com/gif.latex?y_d"> a target function. The minimization problem is subject to the elliptic partial differential equation

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?%5Cbegin%7Bcases%7D%20-%5CDelta%20y%20%3D%20f%20&plus;%20u%20%26%20%5Ctext%7Bin%20%7D%20%5COmega%2C%20%5C%5C%20y%20%3D%200%20%26%20%5Ctext%7Bon%20%7D%20%5CGamma.%20%5Cend%7Bcases%7D">
</p>

We use the steepest descent method based on the adjoint methodology. The corresponding adjoint system writes as

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?%5Cbegin%7Bcases%7D%20-%20%5CDelta%20%5Clambda%20%3D%20y%20-%20y_d%20%26%20%5Ctext%7Bin%20%7D%20%5COmega%2C%20%5C%5C%20%5Clambda%20%3D%200%20%26%20%5Ctext%7Bon%20%7D%20%5CGamma.%20%5Cend%7Bcases%7D">
</p>

The directional derivative of the cost function is given by

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?%5Cmathcal%7BD%7D_%7B%20%5Cdelta%20u%7D%20%5Cmathcal%7BJ%7D%20%5Cleft%28%20u%20%5Cright%29%20%3D%20%5Cint_%7B%5COmega%7D%20%5Cleft%28%20%5Clambda%20&plus;%20%5Cbeta%20u%20%5Cright%29%20%5Cdelta%20u%20%5C%2C%20%5Cmathrm%7Bd%7D%20%5COmega.">
</p>

The control variable is updated according to 

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?u%5E%7B%5Cleft%28%20n%20&plus;%201%20%5Cright%29%7D%20%3D%20u%5E%7B%5Cleft%28%20n%20%5Cright%29%7D%20-%20%5Cepsilon%20%5Cleft%28%20%5Clambda%5E%7B%5Cleft%28%20n%20%5Cright%29%7D%20&plus;%20%5Cbeta%20u%5E%7B%5Cleft%28%20n%20%5Cright%29%7D%20%5Cright%29%2C">
</p>

for some value of <img src="https://latex.codecogs.com/gif.latex?%5Cepsilon">.

## Author

* **Jose Lorenzo Gomez**
* **Víctor Hernández-Santamaría**

## Acknowledgments

This project has received funding from the European Research Council (ERC) under the European  Union’s Horizon 2020 research and innovation programme (grant agreement No. 694126-DyCon).
 
[DyCon Webpage](http://cmc.deusto.eus/dycon/)

## References

* F. Tröltzsch. _Optimal control of partial differential equations: theory, methods, and applications_. American Mathematical Soc., 2010.
