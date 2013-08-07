som-codegen
===========

Testing possible S.implified O.DE M.odels, used to generate code for numerical integrators from LEMS models.

====================================    
The S Ode Model (SOM) specification

example:

{"name" : "izhikevich burster",
 "state": {"v": "v0", "u": "b*v0"},
 "state_functions": {"phi": "0.04 * v**2 + 5*v + 140"},
 "dynamics":  {"v": "phi - u + I", "u": "a * (b * v - u)"},
 "parameters":{"a": "0.02", "b": "0.2", "c": "-50", "d": "2", "I": "0", "v0": "-70"},
 "events": [{"name": "spike", "condition": "v - 30",  "direction" : "+", "effect": {"v": "c", "u": "u + d"}},
            {"name": "start_inj", "condition": "t - 30",  "direction" : "+", "effect": {"I":"15"}},
            {"name": "end_inj", "condition": "t - 150",  "direction" : "+", "effect": {"I": "0"}}],
 "t_start": "0", "t_end": "300", "dt": "0.01"}
    

*Fields:

**name: 
    
**state: object containing 'var name':'initial val' pairs.
    A compact way of determining both state variable names and initial
    values for integration. To be revised, since it introduces
    redundancy (see "dynamics" below).

**state_functions: object containing 'func name':'expression' pairs.
    Auxiliary expressions (possibly) involving parameters and state
    variables. Are always recalculated at each integration step.

**dynamics: object containing 'var name':'expression' pairs.
    Dynamics (in the form of time derivatives) of each state variable.
    Must contain the same key names as the "state" def above.

**parameters: object containing 'par name':'par value' pairs.
     Parameters are expressions which do not have dynamics, i.e. will
     not be integrated. Parameters can be changed through events,
     though.


**events: list of objects with fields
    ***name
    ***condition: expression with format f(x, s, t) = 0 where x,s,t are
        dynamical variables, state functions, parameters or time
    ***direction: "+", "-" or "0" if the condition is met where
        f(x,s,p,t) is increasing, decreasing or both.
    ***effect: object containing state/parameter attributions for when
        condition is met (probably add a "dynamics":{"xi":"dxi/dt"}
        attribute to handle "regime" transitions)
    see relevant discussion at 
http://www.neuron.yale.edu/neuron/static/docs/help/neuron/neuron/classes/cvode.html#Events
    
**t_start

**t_end

**dt