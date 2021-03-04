% distortion vocal effect %

function output = dist(x,g)
   
    output = (x/abs(x))*(1-exp((x/abs(x))*g*x));    %apply distortion function
    
end