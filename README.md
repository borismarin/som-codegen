som-eco
========

moving some SOM elements to ECO, which is in charge of controlling simulations/event handling


Tentative specification
-----------------------

example:
```json
{
    "name": "bouncy_ball", 
    "eco": 
    [{"name": "ball_0", "dynamics": {"x":"v", "v":"-g*x"}, "observables": {"x": 1, "v": 0, "g": 9.8}},
    [{"name": "bounce", "effect":"v=-b*v", "condition": "x == 0"}]
    ],

    "t_start": 0,
    "t_end": 10,
    "output": {"ball_0":["x", "v"]}
}
	    
```    



* Fields:
  * _eco_ (Event COordinator matrix)
  The _eco_ matrix has _n_ rows and _n+1_ columns, where _n_ is the
  number of elements in the network. The first column consists in
  model specification objects with form:

      * _name_: 
    
      * _observables_: object containing 'var name':'val'
      	pairs. Encapsulates both initial conditions for dynamic
        variables and parameters

      * _state_functions_: object containing 'func name':'expression' pairs.
          Auxiliary expressions (possibly) involving parameters and state
          variables. Are always recalculated at each integration step.

      * _dynamics_: object containing 'var name':'expression' pairs.
          Dynamics (in the form of time derivatives) of each state variable.

    The subsequent _n_ columns correspond to event descriptions, where
    M_ij is a list of _event_ objects linking elements _ij_ . Diagonal
    terms correspond to events local to a given element (e.g. spike in
    an IF neuron)

    * _events_: list of objects with fields
        * _name_:

        * _condition_: expression with format f(x, s, t) = 0 where x,s,t are
            dynamical variables, state functions, parameters or time
        * _direction_: "+", "-" or "0" if the condition is met where
            f(x,s,p,t) is increasing, decreasing or both.
        * _effect_: object containing at least one of _state_,
            _parameter_ or _dynamics_ field, defining attributions
            for when _condition_ is met.


    * _t_start_:

    * _t_end_:

    * _dt_:
