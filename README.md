som-eco
========

moving some SOM elements to ECO, which is in charge of controlling simulations/event handling


Tentative specification
-----------------------

example:
```json
{
    "name": "bouncy_ball", 
    "elements": [{"name": "ball", "dynamics": {"x":"v", "v":"-g"}, "parameters": {"g": 9.8, "r": 0.9}}],
    "eco": 
    [
    [{"name": "bounce", "effect":{"v": "-b * v", "x": 0}, "condition": "x - 0", "direction": "-"}]
    ],

    "t_start": 0,
    "t_end": 10,
    "initial_conditions": {"ball_0": {"x":10, "y":0}},
    "output": {"ball":["x", "v"]}
}
	    
```    



* Fields:


  * _elements_ : list of elements in the network
    Elements are specified according to:

      * _name_: 
    
      * _parameters_: object containing 'par name':'par value'
        pairs. Parameters are expressions which do not have dynamics,
        i.e. will not be integrated. Parameters can be changed through
        events, though.
 
      * _state_functions_: object containing 'func name':'expression' pairs.
          Auxiliary expressions (possibly) involving parameters and state
          variables. Are always recalculated at each integration step.

      * _dynamics_: object containing 'var name':'expression' pairs.
          Dynamics (in the form of time derivatives) of each state variable.


  * _eco_ (Event COordinator matrix)
  The _eco_ matrix is square of order _n_ , where _n_ is the number of
  elements in the network. Each entry M_ij is a list of _event_
  objects linking elements _ij_ . Diagonal terms correspond to events
  local to a given element (e.g. spike in an IF neuron)

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

    * _initial_conditions_:

    * _output_: