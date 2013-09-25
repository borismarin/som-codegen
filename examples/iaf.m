
% Matlab script automatically generated from a LEMS/SOM description

function iaf()
    %Integrate the iaf model using matlab odesuite

    X_ = integrate();

    generate_plots(X_)

    dump_output(X_)

end

function X = integrate()

    %parameter list for your convenience
    reset = -0.07;
    C = 3.2e-12;
    thresh = -0.055;
    leakConductance = 2e-10;
    leakReversal = -0.053;


    %assemble parameter array    
    pars = [reset, C, thresh, leakConductance, leakReversal, ];
    
    %initial conditions
    x0_ = [reset, ];
    
   
    t_start = 0;
    t_end = 0.3;
    dt = 1e-05;
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
                v = x0_(1);
                x0_ = [reset, ];
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
   
    v = state(1);


    reset = pars(1);
    C = pars(2);
    thresh = pars(3);
    leakConductance = pars(4);
    leakReversal = pars(5);



    % condition_0
    value(1) = v - thresh;

end

function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    v = state(1);


    reset = pars(1);
    C = pars(2);
    thresh = pars(3);
    leakConductance = pars(4);
    leakReversal = pars(5);


    iSyn = 0;
    iMemb = leakConductance .* (leakReversal - v) + iSyn;


    xdot(1) = iMemb ./ C;

end

function generate_plots(X)

    t = X(:, 1);
    v = X(:, 2);

    figure(1);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([0.0, 0.3, -0.075, -0.05])
    plot(t, v, 'Color', hex2rgb('#FF0000'))
    plot(t, v, 'Color', hex2rgb('#D7DF01'))
    plot(t, v, 'Color', hex2rgb('#01DF3A'))
    plot(t, v, 'Color', hex2rgb('#0174DF'))

end

function dump_output(X)
    disp(['Dumping timeseries to file ', 'results/iaf_v.dat'])
    save('results/iaf_v.dat', 'X', '-ascii');
end

function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
