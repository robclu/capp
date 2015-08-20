clear all;
close all;

% Load aspect results
atimes1 = importdata('bsaresults1.txt');
atimes2 = importdata('bsaresults2.txt');
atimes3 = importdata('bsaresults3.txt');

% Load in non-aspect results
natimes1 = importdata('bsnaresults1.txt');
natimes2 = importdata('bsnaresults1.txt');
natimes3 = importdata('bsnaresults1.txt');

% Load in sequential results
stimes1 = importdata('bssresults1.txt');
stimes2 = importdata('bssresults1.txt');
stimes3 = importdata('bssresults1.txt');

% Calculate the means of each dataset
atimes_mean = get_mean( atimes1, atimes2, atimes3 );
natimes_mean = get_mean( natimes1, natimes2, natimes3 );
stimes_mean = get_mean( stimes1, stimes2, stimes3 );

figure();
hold all;
plot( stimes_mean(:,1) .* 10e-7, stimes_mean(:,2) .* 10e-9, '-bx');
plot( atimes_mean(:,1) .* 10e-7, atimes_mean(:,2) .* 10e-9, '-rx');
plot( natimes_mean(:,1) .* 10e-7, natimes_mean(:,2) .* 10e-9, '-gx');
xlim([0 7]);
legend('CPU', 'CAPP','OpenCL', 'location', 'northwest');
title('Graph Showing Run-time vs. No. Options for the Black-Scholes Option Pricing Problem');
ylabel('Time (seconds)');
xlabel('Options Evaluated (Millions)')
