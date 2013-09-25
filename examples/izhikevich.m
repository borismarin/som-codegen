
% Matlab script automatically generated from a LEMS/SOM description

function izhikevich_burster()
    %Integrate the izhikevich_burster model using matlab odesuite

    X_ = integrate();



end

function X = integrate()

    %parameter list for your convenience
    a = 0.02;
    b = 0.2;
    c = -50;
    d = 2;
    I = 0;
    v0 = -70;


    %assemble parameter array    
    pars = [a, b, c, d, I, v0, ];
    
    %initial conditions
    x0_ = [v0, b .* v0, ];
    
   
    t_start = 0;
    t_end = 300;
    dt = 0.01;
    tint = t_start:dt:t_end;
    options = odeset('RelTol', 1e-6);
    options = odeset(options, 'Events',@(t,y) events(t, y, pars));
    %output initialization
    tout = t_start;
    xout = x0_;
    teout = [];
    xeout = [];
    ieout = [];


    while (1)
        [t_, x_, te_, xe_, ie_] = ode45(@(t, x) dxdt(t, x, pars), tint, x0_, options);
        x0_ = x_(end,:);
        tout = [tout; t_(2:end-1)];
        xout = [xout; x_(2:end-1, :)];
        teout = [teout; te_];
        xeout = [xeout; xe_];
        ieout = [ieout; ie_];
    
        if (te_)
            %stopped at event
            switch ieout(end)

                case 1 
                %spike
                v = x0_(1);
                u = x0_(2);
                x0_ = [c, u + d, ];

                case 2 
                %start_inj
                I = 5;

                pars = [a, b, c, d, I, v0, ];

                case 3 
                %end_inj
                I = 0;

                pars = [a, b, c, d, I, v0, ];
            end
        else 
            %stopped at t_end
            break
        end
        
        %restart from discontinuity
        options = odeset(options, 'InitialStep', t_(end)-t_(end-1), 'MaxStep', t_(end)-t_(1));
        tint = [t_(end), tout(end)+dt:dt:t_end];

    end

    %plot(tout, xout, '-', teout, xeout, '*r')    

    X = [tout, xout];

end


function [value,isterminal,direction] = events(t, state, pars)
    value = [1,1,1,];
    isterminal = [1,1,1,];
    direction = [1,1,1,];
   
    v = state(1);
    u = state(2);


    a = pars(1);
    b = pars(2);
    c = pars(3);
    d = pars(4);
    I = pars(5);
    v0 = pars(6);



    % spike
    value(1) = v - 30;

    % start_inj
    value(2) = t - 30.0001;

    % end_inj
    value(3) = t - 150.0001;

end

function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    v = state(1);
    u = state(2);


    a = pars(1);
    b = pars(2);
    c = pars(3);
    d = pars(4);
    I = pars(5);
    v0 = pars(6);


    phi = 0.04 .* v .^ 2 + 5 .* v + 140;


    xdot(1) = phi - u + I;
    xdot(2) = a .* (b .* v - u);

end

function generate_plots(X)

    t = X(:, 1);
    v = X(:, 2);
    u = X(:, 3);

end


function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
