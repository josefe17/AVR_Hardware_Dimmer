clear, clc, close all

dimming_steps=256;

firing_resolution_bits=16;

file_out = 'linearCurve_16bit_rom.h';

%% Compute linear Vrms curve
Vn=linspace(0, 1, dimming_steps);

Pn_numeric=Vn.^2;

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
linear_RMS_rom='const unsigned int linearCurveFiringTable[] PROGMEM = { ';
for k=1:dimming_steps-1
    linear_RMS_rom = [linear_RMS_rom, num2str(uint16(duties(k))), ', '];
end
linear_RMS_rom=[linear_RMS_rom, num2str(uint16(duties(end))), ' };'];

%linear_RMS_rom

%% Store ROM
fileID = fopen(file_out,'w');
fprintf(fileID, linear_RMS_rom);
fclose(fileID);
