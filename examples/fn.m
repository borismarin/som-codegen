
% Matlab script automatically generated from a LEMS/SOM description

function fn1()
    %Integrate the fn1 model using matlab odesuite

    X_ = integrate();

    generate_plots(X_)

    dump_output(X_)

end

function X = integrate()

    %parameter list for your convenience
    I = 0.8;
    SEC = 1.0;


    %assemble parameter array    
    pars = [I, SEC, ];
    
    %initial conditions
    x0_ = [0, 0, ];
    
   
    t_start = 0;
    t_end = 200.0;
    dt = 0.05;
    tint = t_start:dt:t_end;
    options = odeset('RelTol', 1e-6);
    [tout, xout] = ode45(@(t, x) dxdt(t, x, pars), tint, x0_, options);



    X = [tout, xout];

end


function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    W = state(1);
    V = state(2);


    I = pars(1);
    SEC = pars(2);




    xdot(1) = 0.08 .* (V + 0.7 - 0.8 .* W) ./ SEC;
    xdot(2) = (V - V .^ 3 ./ 3 - W + I) ./ SEC;

end

function generate_plots(X)

    t = X(:, 1);
    W = X(:, 2);
    V = X(:, 3);

    figure(1);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([0.0, 200.0, -2.5, 2.5])
    plot(t, V, 'Color', hex2rgb('#ee40FF'))
    plot(t, W, 'Color', hex2rgb('#BBA0AA'))

end

function dump_output(X)
    disp(['Dumping timeseries to file ', 'results/fn.dat'])
    save('results/fn.dat', 'X', '-ascii');
end

function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
