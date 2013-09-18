
% Matlab script automatically generated from a LEMS/SOM description

function Locke2008_Circadian_Clock_0()
    %Integrate the Locke2008_Circadian_Clock_0 model using matlab odesuite

    X_ = integrate();

    generate_plots(X_)

    dump_output(X_)

end

function X = integrate()

    %parameter list for your convenience
    Kc = 4.8283;
    v_4 = 1.0841;
    v_6 = 4.6645;
    vc = 6.7924;
    v_1 = 6.8355;
    v_2 = 8.4297;
    K = 1.0;
    v_8 = 3.5216;
    L = 0.0;
    n = 5.6645;
    k3 = 0.1177;
    K2 = 0.291;
    K1 = 2.7266;
    k7 = 0.2282;
    K6 = 9.9849;
    k5 = 0.3352;
    K4 = 8.1343;
    K8 = 7.4519;
    init_X1 = 4.25;
    tscale = 1.0;
    init_Z1 = 2.25;
    init_Z2 = 0.0;
    init_V1 = 2.5;
    init_V2 = 0.0;
    init_X2 = 0.0;
    compartment = 1.0;
    init_Y1 = 3.25;
    init_Y2 = 0.0;


    %assemble parameter array    
    pars = [Kc, v_4, v_6, vc, v_1, v_2, K, v_8, L, n, k3, K2, K1, k7, K6, k5, K4, K8, init_X1, tscale, init_Z1, init_Z2, init_V1, init_V2, init_X2, compartment, init_Y1, init_Y2, ];
    
    %initial conditions
    x0_ = [init_Y2, init_V1, init_Y1, init_V2, init_X2, init_X1, init_Z1, init_Z2, ];
    
   
    t_start = 0;
    t_end = 50.0;
    dt = 0.005;
    tint = t_start:dt:t_end;
    options = odeset('RelTol', 1e-6);
    [tout, xout] = ode45(@(t, x) dxdt(t, x, pars), tint, x0_, options);



    X = [tout, xout];

end


function xdot = dxdt(t, state, pars)
    xdot = zeros(length(state),1);

    Y2 = state(1);
    V1 = state(2);
    Y1 = state(3);
    V2 = state(4);
    X2 = state(5);
    X1 = state(6);
    Z1 = state(7);
    Z2 = state(8);


    Kc = pars(1);
    v_4 = pars(2);
    v_6 = pars(3);
    vc = pars(4);
    v_1 = pars(5);
    v_2 = pars(6);
    K = pars(7);
    v_8 = pars(8);
    L = pars(9);
    n = pars(10);
    k3 = pars(11);
    K2 = pars(12);
    K1 = pars(13);
    k7 = pars(14);
    K6 = pars(15);
    k5 = pars(16);
    K4 = pars(17);
    K8 = pars(18);
    init_X1 = pars(19);
    tscale = pars(20);
    init_Z1 = pars(21);
    init_Z2 = pars(22);
    init_V1 = pars(23);
    init_V2 = pars(24);
    init_X2 = pars(25);
    compartment = pars(26);
    init_Y1 = pars(27);
    init_Y2 = pars(28);


    rate__R6 = compartment .* v_4 .* Y1 ./ compartment ./ (K4 + Y1 ./ compartment);
    rate__R7 = compartment .* k5 .* Y1 ./ compartment;
    rate__R4 = compartment .* L;
    rate__R5 = compartment .* k3 .* X1 ./ compartment;
    rate__R2 = compartment .* v_2 .* X1 ./ compartment ./ (K2 + X1 ./ compartment);
    rate__R1 = compartment .* v_1 .* K1 .^ n ./ (K1 .^ n + (Z1 ./ compartment) .^ n);
    F = 1.0 ./ 2.0 .* (V1 + V2);
    rate__R3 = compartment .* vc .* K .* F ./ (Kc + K .* F);
    rate__R8 = compartment .* v_6 .* Z1 ./ compartment ./ (K6 + Z1 ./ compartment);
    rate__R9 = compartment .* k7 .* X1 ./ compartment;
    rate__R14 = compartment .* L;
    rate__R15 = compartment .* k3 .* X2 ./ compartment;
    rate__R16 = compartment .* v_4 .* Y2 ./ compartment ./ (K4 + Y2 ./ compartment);
    rate__R17 = compartment .* k5 .* Y2 ./ compartment;
    rate__R10 = compartment .* v_8 .* V1 ./ compartment ./ (K8 + V1 ./ compartment);
    rate__R11 = compartment .* v_1 .* K1 .^ n ./ (K1 .^ n + (Z2 ./ compartment) .^ n);
    rate__R12 = compartment .* v_2 .* X2 ./ compartment ./ (K2 + X2 ./ compartment);
    rate__R13 = compartment .* vc .* K .* F ./ (Kc + K .* F);
    rate__R20 = compartment .* v_8 .* V2 ./ compartment ./ (K8 + V2 ./ compartment);
    rate__R18 = compartment .* v_6 .* Z2 ./ compartment ./ (K6 + Z2 ./ compartment);
    rate__R19 = compartment .* k7 .* X2 ./ compartment;


    xdot(1) = tscale .* (rate__R15 - rate__R16);
    xdot(2) = tscale .* (rate__R9 - rate__R10);
    xdot(3) = tscale .* (rate__R5 - rate__R6);
    xdot(4) = tscale .* (rate__R19 - rate__R20);
    xdot(5) = tscale .* (rate__R11 - rate__R12 + rate__R13 + rate__R14);
    xdot(6) = tscale .* (rate__R1 - rate__R2 + rate__R3 + rate__R4);
    xdot(7) = tscale .* (rate__R7 - rate__R8);
    xdot(8) = tscale .* (rate__R17 - rate__R18);

end

function generate_plots(X)

    t = X(:, 1);
    Y2 = X(:, 2);
    V1 = X(:, 3);
    Y1 = X(:, 4);
    V2 = X(:, 5);
    X2 = X(:, 6);
    X1 = X(:, 7);
    Z1 = X(:, 8);
    Z2 = X(:, 9);

    figure(1);
    hold on;
    % uncomment below to bypass autoscaling
    %axis([0.0, 50.0, 1.0, 0.0])
    plot(t, X1, 'Color', hex2rgb('#000000'))
    plot(t, Y1, 'Color', hex2rgb('#ff0000'))
    plot(t, Z1, 'Color', hex2rgb('#00ff00'))
    plot(t, V1, 'Color', hex2rgb('#0000ff'))
    plot(t, X2, 'Color', hex2rgb('#ff00ff'))
    plot(t, Y2, 'Color', hex2rgb('#00ffff'))
    plot(t, Z2, 'Color', hex2rgb('#ffff00'))
    plot(t, V2, 'Color', hex2rgb('#ffc800'))

end

function dump_output(X)
    disp(['Dumping timeseries to file ', 'Locke2008_Circadian_Clock.dat'])
    save('Locke2008_Circadian_Clock.dat', 'X', '-ascii');
end

function c = hex2rgb(hexstring)
    f = @(i) hex2dec(hexstring(i:i+1))/255;
    c = arrayfun(f, 2:2:6);
end
