
% Matlab script automatically generated from a LEMS/SOM description

function hr_chaotic()
    %Integrate the hr_chaotic model using matlab odesuite

    X_ = integrate();

    generate_plots(X_)


end

function X = integrate()

    %parameter list for your convenience
    a = 1.0;
    c = 1.0;
    b = 2.8;
    d = 5.0;
    I = 3.94;
    s = 4.0;
    r = 0.01;
    y0 = -1.0;
    x0 = -1.6;
    x1 = -1.6;
    z0 = 1.0;
    SEC = 1.0;


    %assemble parameter array    
    pars = [a, c, b, d, I, s, r, y0, x0, x1, z0, SEC, ];
    
    %initial conditions
    x0_ = [y0, x0, z0, ];
    
   
    t_start = 0;
    t_end = 2000.0;
    dt = 0.01;
    tint = t_start:dt:t_end;
    options = odeset('RelTol', 1e-3);
    [tout, xout] = ode45(@(t, x) dxdt(t, x, pars), tint, x0_, options);



    X = [tout, xout];

end


function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    y = state(1);
    x = state(2);
    z = state(3);


    a = pars(1);
    c = pars(2);
    b = pars(3);
    d = pars(4);
    I = pars(5);
    s = pars(6);
    r = pars(7);
    y0 = pars(8);
    x0 = pars(9);
    x1 = pars(10);
    z0 = pars(11);
    SEC = pars(12);


    Q = c - d .* x .^ 2 - y;
    P = y - a .* x .^ 3 + b .* x .^ 2 + I;
    R = s .* (x - x1) - z;


    xdot(1) = Q ./ SEC;
    xdot(2) = (P - z) ./ SEC;
    xdot(3) = r .* R ./ SEC;

end

function generate_plots(X)

    t = X(:, 1);
    y = X(:, 2);
    x = X(:, 3);
    z = X(:, 4);

    figure(1);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([-100.0, 2100.0, -2.0, 2.0])
    plot(t, x, 'Color', hex2rgb('#000000'))

end


function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
