
% Matlab script automatically generated from a LEMS/SOM description

function hr_chaotic_flat()
    %Integrate the hr_chaotic_flat model using matlab odesuite

    X_ = integrate();

    generate_plots(X_)


end

function X = integrate()

    %parameter list for your convenience
    a = 1.0;
    b = 2.8;
    c = 1.0;
    d = 5.0;
    I = 3.94;
    r = 0.01;
    s = 4.0;
    x1 = -1.6;
    thresh = 1.0;
    x0 = -1.6;
    y0 = -1.0;
    z0 = 1.0;
    SEC = 1.0;


    %assemble parameter array    
    pars = [a, b, c, d, I, r, s, x1, thresh, x0, y0, z0, SEC, ];
    
    %initial conditions
    x0_ = [x0, y0, z0, ];
    
   
    t_start = 0;
    t_end = 2000.0;
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
                %x__gt__thresh
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

    X = [tout, xout, teout', xeout'];

end


function [value,isterminal,direction] = events(t, state, pars)
    value = [1,];
    isterminal = [1,];
    direction = [1,];
   
    x = state(1);
    y = state(2);
    z = state(3);


    a = pars(1);
    b = pars(2);
    c = pars(3);
    d = pars(4);
    I = pars(5);
    r = pars(6);
    s = pars(7);
    x1 = pars(8);
    thresh = pars(9);
    x0 = pars(10);
    y0 = pars(11);
    z0 = pars(12);
    SEC = pars(13);



    % x__gt__thresh
    value(1) = x - thresh;

end

function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    x = state(1);
    y = state(2);
    z = state(3);


    a = pars(1);
    b = pars(2);
    c = pars(3);
    d = pars(4);
    I = pars(5);
    r = pars(6);
    s = pars(7);
    x1 = pars(8);
    thresh = pars(9);
    x0 = pars(10);
    y0 = pars(11);
    z0 = pars(12);
    SEC = pars(13);


    P = y - a .* x .^ 3.0 + b .* x .^ 2.0 + I;
    Q = c - d .* x .^ 2.0 - y;
    R = s .* (x - x1) - z;


    xdot(1) = (P - z) ./ SEC;
    xdot(2) = Q ./ SEC;
    xdot(3) = r .* R ./ SEC;

end

function generate_plots(X)

    t = X(:, 1);
    x = X(:, 2);
    y = X(:, 3);
    z = X(:, 4);
    te = X(:,5);
    xe = X(:,6);

    figure(1);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([-100, 2100, -2, 2])
    plot(t, x, 'Color', hex2rgb('#000000'), te, xe, 'o')
    

    figure(2);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([-100, 2100, -6, 1])
    plot(t, y, 'Color', hex2rgb('#0000ff'))

    figure(3);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([-100, 2100, 3, 4])
    plot(t, z, 'Color', hex2rgb('#00ff00'))
    
end


function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
