function [ mean ] = get_mean( in1, in2, in3 )

    % Create a new matrix 
    mean_temp = zeros( length(in1(:,1)), length(in1(1,:)) );    
    for i = 1 : length( mean_temp(:, 1) )
        mean_temp(i, 1) = in1(i, 1);
        mean_temp(i,2) = max( [in1(i, 2) in2(i, 2) in3(i, 2)] ) ;
    end
    
    mean = mean_temp;
end

