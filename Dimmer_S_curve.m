clear, clc, close all

dimming_steps=256;

firing_resolution_bits=16;

file_out = 'SCurve_16bit_rom.h';

%% Compute linear power curve
Pn_numeric=linspace(0, 1, dimming_steps);

syms duty Pn

eq1 = (2*pi*(1-Pn) == (2*pi*duty)- sin(2*pi*duty));

eq1_num =subs(eq1, 'Pn', Pn_numeric);

duties=zeros(1, dimming_steps);
for k=1:dimming_steps
    duties(k)=vpasolve(eq1_num(k), duty);
end

%% Plot 

plot(duties)
hold on
plot(1-duties)

figure(2)
duties2=duties*pi;

Vn2= real(sqrt((1/pi)*(pi-duties2+(1/2)*sin(2*duties2))));

plot(Vn2)
hold on
plot(Vn2.^2)

%% Prepare rom

duties=duties*2^firing_resolution_bits;
linear_power_rom='const unsigned int SCurveFiringTable[] PROGMEM = { ';;
for k=1:dimming_steps-1
    linear_power_rom = [linear_power_rom, num2str(uint16(duties(k))), ', '];
end
linear_power_rom=[linear_power_rom, num2str(uint16(duties(end))), ' };'];

%linear_power_rom

%% Store ROM
fileID = fopen(file_out,'w');
fprintf(fileID, linear_power_rom);
fclose(fileID);
