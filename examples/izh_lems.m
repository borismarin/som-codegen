
% Matlab script automatically generated from a LEMS/SOM description

function izClass1()
    %Integrate the izClass1 model using matlab odesuite

    X_ = integrate();



end

function X = integrate()

    %parameter list for your convenience
    a = 0.02;
    c = -55.0;
    b = -0.1;
    d = 6.0;
    v0 = -0.06;
    thresh = 0.03;
    MVOLT = 0.001;
    MSEC = 0.001;


    %assemble parameter array    
    pars = [a, c, b, d, v0, thresh, MVOLT, MSEC, ];
    
    %initial conditions
    x0_ = [v0 .* b ./ MVOLT, v0, ];
    
   
    t_start = 0;
    t_end = 0.2;
    dt = 5e-06;
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
                %condition_0
                U = x0_(1);
                v = x0_(2);
                x0_ = [U + d, c .* MVOLT, ];
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
    value = [1,];
    isterminal = [1,];
    direction = [1,];
   
    U = state(1);
    v = state(2);


    a = pars(1);
    c = pars(2);
    b = pars(3);
    d = pars(4);
    v0 = pars(5);
    thresh = pars(6);
    MVOLT = pars(7);
    MSEC = pars(8);



    % condition_0
    value(1) = v - thresh;

end

function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    U = state(1);
    v = state(2);


    a = pars(1);
    c = pars(2);
    b = pars(3);
    d = pars(4);
    v0 = pars(5);
    thresh = pars(6);
    MVOLT = pars(7);
    MSEC = pars(8);


    ISyn = 0;


    xdot(1) = a .* (b .* v ./ MVOLT - U) ./ MSEC;
    xdot(2) = (0.04 .* v .^ 2 ./ MVOLT + 5 .* v + (140.0 - U + ISyn) .* MVOLT) ./ MSEC;

end

function generate_plots(X)

    t = X(:, 1);
    U = X(:, 2);
    v = X(:, 3);

end


function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
