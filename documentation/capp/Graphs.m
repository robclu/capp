close all;
clear all;

% SAXPY Plot

% Data sizes
data_sizes = [(2048) (2048*4) (2048*4^2) (2048*4^3) (2048*4^4) (2048*4^5)];

% CPU results 
cpu = [232666 279992 2649316 12286319 37256534 114412990];

% OpenCL no aspects
ocl = [76134510 66385079 69415393 69497045 69541617 68737104];

% APP
app = [73074460 66071780 76834095 67338283 65109403 70788220];

app = app .* 10e-9;
cpu = cpu .* 10e-9;
ocl = ocl .* 10e-9;

hold on;
plot(data_sizes, cpu, '-bx');
plot(data_sizes, ocl, '-rx');
plot(data_sizes, app, '-gx');
xlim([0 2048*4^5 + 5]);
xlabel('Vector Size (Number of Elements)');
ylabel('Time (s)');
legend('CPU', 'OpenCL', 'APP');
