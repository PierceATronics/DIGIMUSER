function y = iircomb(x, C, g, M)
    % Implements the IIR Comb Filter.
    %   Difference EQ: y[n] = Cx[n] + gy[n - M]
    %   Transfer Func: H(z) = c / (1 - gz^-M);
    delay = zeros(1, length(x) + M);
    y = zeros(1, length(x));
    for idx=1:length(x)
        y(idx) = C.*x(idx) + g.*delay(idx);
        delay(idx + M) = y(idx);
    end
        
end