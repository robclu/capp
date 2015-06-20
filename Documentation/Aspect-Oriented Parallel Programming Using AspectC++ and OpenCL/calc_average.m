function [ results ] = calc_average( num_inputs, filename, file_ext )
   
% Get the first input
input = importdata( strcat( filename, num2str(1), file_ext ) );

% Declare result array
results = zeros( length( input( :, 1 ) ), 2 );

% Copy first column
results( :, 1 ) = input( :, 1 );

% Load all the files
for i = 1 : num_inputs
    file = strcat( filename, num2str( i ), file_ext );
    input = importdata( file );
    
    % Move values into matrix
    results( :, 2 ) = results( :, 2 ) + input( :, 2 );
end 

% Average 
results( :, 2 ) = results( :, 2 ) / (num_inputs );

end

