dLEMS  
===== [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.1345748.svg)](https://doi.org/10.5281/zenodo.1345748)



*dLEMS* (distilled LEMS) is a [JSON](http://www.json.org/) based format, used to
generate code for numerical integrators from LEMS models.

Work in progress! Expect major changes!


Specification (in progress)
---------------------------

Example illustrating supported constructs:

```json
{
    "name":"izhikevich_burster",
    "state":{
        "v":"v0",
        "u":"b*v0"
    },
    "state_functions":{
        "phi":"0.04 * v**2 + 5*v + 140"
    },
    "dynamics":{
        "v":"phi - u + I",
        "u":"a * (b * v - u)"
    },
    "parameters":{
        "a":"0.02",
        "b":"0.2",
        "c":"-50",
        "d":"2",
        "I":"0",
        "v0":"-70"
    },
    "events":[
        {
            "name":"spike",
            "condition":"v - 30",
            "direction":"+",
            "effect":{
                "state":{
                    "v":"c",
                    "u":"u + d"
                }
            }
        },
        {
            "name":"start_inj",
            "condition":"t - 30",
            "direction":"+",
            "effect":{
                "parameters":{
                    "I":"5"
                }
            }
        },
        {
            "name":"end_inj",
            "condition":"t - 150",
            "direction":"+",
            "effect":{
                "parameters":{
                    "I":"0"
                }
            }
        }
    ],
    "t_start":"0",
    "t_end":"300",
    "dt":"0.01",

    "display": [
        {
            "abscissa_axis": {
                "max": "-2.",
                "min": "-16.0"
            },
            "ordinate_axis": {
                "max": "50.0",
                "min": "-90.0"
            },
            "curves": [
                {
                    "abscissa": "t",
                    "ordinate": "v",
                    "colour": "#ee40FF"
                },
                {
                    "abscissa": "t",
                    "ordinate": "u",
                    "colour": "#BBA0AA"
                }
            ]
        }
    ]
}

```    

* Fields:

    * _name_: the name of the component being described
    
    * _state_: object containing 'var name':'initial val' pairs.
        A compact way of determining both state variable names and initial
        values for integration. To be revised, since it introduces
        redundancy (see "dynamics" below).

    * _state_functions_: object containing 'func name':'expression' pairs.
        Auxiliary expressions (possibly) involving parameters and state
        variables. Are always recalculated at each integration step.

    * _dynamics_: object containing 'var name':'expression' pairs.
        Dynamics (in the form of time derivatives) of each state variable.
        Must contain the same key names as the "state" def above.

    * _parameters_: object containing 'par name':'par value' pairs.
        Parameters are expressions which do not have dynamics, i.e. will
        not be integrated. Parameters can be changed through events,
        though.

    * _events_: list of objects with fields
        * _name_:
        * _condition_: expression with format f(x, s, t) = 0 where x,s,t are
            dynamical variables, state functions, parameters or time
        * _direction_: "+", "-" or "0" if the condition is met where
            f(x,s,p,t) is increasing, decreasing or both.
        * _effect_: object containing at least one of _state_ or
            _parameter_ field, defining attributions for when
            _condition_ is met.
    
    * _t_start_:

    * _t_end_:

    * _dt_:
    
Notes
-----

Currently, only isolated LEMS components (no populations or networks) are
supported; check the _eco-som_ branch for a tentive multi-component
format.
