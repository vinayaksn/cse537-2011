# Introduction #
Electric and Hybrid electric vehicles are increasing in popularity and demand due to the rising fuel prices and concerns towards the rising CO<sub>2</sub> content in the atmosphere as world is more aware.
Consumers are embracing environmentally friendly "green cars" as a result of the rising cost of fossil fuels and a growing concern for the health of the environment.
Sales forecasts predict that green car sales will comprise 20%–25% of all vehicle sales by the year 2015.
The hybrid electric vehicle (HEV) is quickly becoming the most popular green car and by 2015 is expected to comprise approximately 12% of global vehicle sales.
Another class of cars that are growing are electric cars which right now are low in number but is going to be the thing to turn to after fuel becomes scarce for Hybrid vehicles as these solely run on the battery and hence battery management is an even bigger task here.
Hybrid electric vehicles employ complex power electronic circuitry to control the flow of electric energy through the vehicle.


# Contents #
  1. Hybrid Electric Vehicles (Need /Types)
  1. Working
  1. Need for Battery Management
  1. Process of Battery Management
  1. Factors affecting Battery Performance
  1. Future

# Hybrid Electric Vehicles (HEVs) #

> In order to address the problems of

  1. Rising fuel prices
  1. Global Warming
  1. Pollution

> the Electric Vehicles(EVs) came into existence. But they are still unable to penetrate into the consumer market. One of the major reason of the lack of acceptance of EVs powered by battery could be the presence of only 1 source of power i.e. battery, which makes it less usable as even the advanced battery system could only support 140 to 150 kms at one go. So after every 100 to 150 kms you need to recharge your battery overnight and due to low of number of recharging stations, you can't rely only on the battery powered vehicle for long distance travel.

Some of the advantages of such vehicles could be-
  1. The presence of both gasoline and electric vehicles renders the best of both worlds.
  1. About two times more efficient than the traditional internal combustion engine.
  1. It has equivalent power, range, cost and safety of a conventional vehicle while reducing fuel costs and harmful emissions.
  1. The battery is continuously recharged by a motor/generator driven by the Internal Combustion Engine (ICE) or by regenerative braking.

Examples of such cars are:
  1. Toyota Prius
  1. Honda Civic
  1. Honda Insight
  1. Honda Accord
  1. Ford Escape

# Mechanism #
The mechanisms that electric and hybrid electric vehicles use to recharge their batteries are:
  1. _Regenerative Braking_ : This mechanism help the car convert its kinetic energy into electrical energy of the battery instead of letting it go waste as heat by the usual brake mechanism. While braking the rotors slow down the car while charging the battery.
  1. _Electrical Generator_: This is the conventional way of recharging the battery as this convert mechanical energy in electrical energy.

> The _Controller Area Network (CAN)_ uses high-speed communication busses to facilitate communication between the microprocessors and the various control systems. For example, battery management systems, transmission controller, engine controller, etc.
The following video gives a brief overview of the working of HEVs-

<a href='http://www.youtube.com/watch?feature=player_embedded&v=2HrQeGzIZoI' target='_blank'><img src='http://img.youtube.com/vi/2HrQeGzIZoI/0.jpg' width='425' height=344 /></a>

# Need for Battery Management #

For operating at its full efficiency, a hybrid car must use the full capacity of its battery during each discharge cycle, i.e. when the car is running on electric motors and the internal combustion engine is not consuming any energy. In such scenario if the battery control system turns the internal combustion engine on before the battery is fully discharged, the fuel consumption is increased which is totally opposite to its aim of increasing the efficiency and reducing the overall fuel consumption.

# Types of batteries #
> As there are many types of electric and hybrid electric vehicles which are used according to specifications and the power needed by the electric motor of the car. The most commonly used batteries are:
  1. _Li-Ion battery_-Experience with laptop computers is showing that Li-ion cells degrade under float conditions:  extended operation when held at 100% SOC decreases operating life.Life testing in telecom applications shows that limiting the upper end charge voltage reduces degradation substantially.The effect is similar to limiting SOC to less than 90%.The curve shown earlier shows rapid imbalance and capacity reduction below 20% SOC.Key problem:  cellbalancing – no inherent mechanism in Li-ion.Typical systems useresistive limiters toenforce the upper voltage limit.Limiters add system nonlinearity that drives (lossy) cell balancing at the top end of SOC. Balancing is more important at the low end, where discharge effects begin to pull cells apart.In reality, a method is needed that can balance over the entire useful SOC range.When this is done, the possible range of SOC becomes 20% to 90%.If the cells achieve 200 W-h/kg for 100% discharge, the effective energy density is 140 W-h/kg – more than triple the best NiMH results.
  1. _NiMH Battery_-Extensive data in preparation for and from experience with commercial hybrids.Toyota has had fewproblems with Priustraction batteries –routine replacementhas not been required.Limited SOC swing – about 50% to 65%.Given density of 70 W-h/kg for full discharge, the effective density is less than 10 W-h/kg.The argument can be made that these designs use nickel-metal-hydride batteries for the functions of ultracapacitors.What aspects is this application attempting to optimize?At the high end, positive electrode degradation and electrolyte loss occurs.Positive pressure can transfer hydrogen among adjacent cells but amplifies degradation and imbalances cells.At the low end, the negative electrode experiences irreversible oxidation.Impedance rises for discharge.High-end effects are minimized if SOC is limited well below 80%.Low-end effects are strong below 20% SOC, but performance degrades to some degree below 40% SOC.External active balancing helps maintain discharge performance between 20% and 40% SOC, and limits degradation above 80%.
  1. _Lead Acid battery_(rarely used)-Operating results from starting-lighting-ignition (SLA) batteries.Consistent with float operation in telecom.Best life results above 85% SOC.But the top end involves gassing reactions and sacrifices efficiency.Energy density is about 35 W-h/kg given 100% discharge cycles.Effective energy density (15%) is5.3 W-h/kg.
Ultracapacitors can do as well.Cells show damage from sulfation when operated at lower SOC.Present designs should be able to support an SOC range of 50% to 100%, but only if the batteries are stored full.
Promising future designs are likely to correct the most severe damagemechanisms.Do not favor HEV and EVapplications except on a“use, park, charge” cycle.


These cars use different mechanisms to recharge these batteries and mainly use the electric engine at lower speeds.

# Factors Affecting Battery Performance #
There are  a number of factors affecting batteries in vehicle hence it is important to have effecient battery management. The factors affecting battery life are :
  1. _Temperature_ :Temperature has severe affects on battery performance and these affects depend greatly on the battery chemistry used. A rule of thumb for temperature degradation is that battery performance will decrease by 35% at either the upper or lower range of the specified operating threshold, outside the threshold the battery may not                     work at all.
  1. _DOD(Depth of Discharge)_ : Batteries are able to maintain their performance longer when they are not deeply discharged regularly.
  1. _Charging_: The level of charging, the voltage at which the battery is charged and for how long at a stretch also affects the battery as charging the battery for too long might damage it and other such factors.
  1. _Voltage affects_ : Rechargeable batteries each have a characteristic working voltage range associated with the particular cell chemistry employed. The practical voltage limits are a consequence of the onset of undesirable chemical reactions which take place beyond the safe working range.
  1. _Power to weight ratio_ : The battery capacity also depends on the weight of the vehicle as we need more and more powerful batteries for heavier vehicles.
  1. _Other factors_ : factors like cell ageing, weather, usage, maintainance, etc. also affect the battery and these should also be catered to.

# Battery Management System #
> BMS for hybrid cars consists of a _battery_, a _generator_ which only produces electric power and an _electric motor_ which can act as both a motor and a generator. For example, it can draw energy from the batteries to accelerate the car and it can also slow down the car down and return energy to the batteries.

> _SOC_: The State of Charge of a battery is its available capacity expressed as a percentage of its rated capacity

# Overall Process #
  1. Various sensors-temperature, voltage, current report to Main Unit.
  1. Respective comparators compare with the threshold.
  1. If above the specified threshold-
    1. warn by displaying on LED, activating a buzzer.
    1. if critical then cutting off the battery supply.

# Research #
Frazer–Nash and Henry Ronald Godfrey formed Frazer-Nash to produce affordable motor vehicles.
The FN BMS is available in two formats:

  1. Standard Format: The BMS is offered with the Slaves in an industry standard half Eurocard format, which allows the user to quickly develop a prototype system to evaluate the performance and establish suitability of the system as a whole.
  1. Integrated Format: Experience has shown that by integrating the design of the BMS with the mechanical design of the battery pack as a whole then substantial savings in size, weight and cost can be achieved.

# Forecast #
Over the past decade, there has been a considerable amount of growth in the battery technology which has been triggered by the need for better performance of such batteries. A survey done on batteries for electric cars by Boston Consultancy Group puts forward 6 dimensions on which the current Li-ion batteries can be evaluated.These are: safety, lifespan, performance, specific energy, specific power and cost. Out of these, cost and performance become the two major hurdles for electric cars.

According to a survey by bcg.com , the battery costs will decline steeply till 2020 as the production volume increases. Cost for equipments, individual parts and also the growing levels of automation should trim the cost. Around 70% of the hybrid cars would be using Li-ion batteries and 30% using Ni-Mh batteries till 2020. According to a survey done by pikeresearch.com , vehicles will slowly move from Li-ion to NiMH technology thus reducing the cost. According to the analysis given by bcg.com , the amount that an equipment manufacturer will have to pay will decrease around 60-65% from 2009-2020. Hence the price to consumers will also fall $1400 – $1800 per KWh to $570 - $700 per KWh.

# References #
  1. http://www.nrel.gov/vehiclesandfuels/energystorage/pdfs/3a_2002_01_1918.pdf
  1. http://www.dolcera.com/wiki/index.php?title=Hybrid_Electric_Vehicle_Battery_System
  1. http://www.automobile-hibride.ro/imagini/txt/articole_diverse/Paper_06_Buretea_ESFA.pdf
  1. http://www.allhybridcars.com/hybrid-car-faqs.html
  1. http://www.mpoweruk.com/bms.htm
  1. http://www.mpoweruk.com/life.htm
  1. http://en.wikipedia.org/wiki/Battery_management_system
  1. http://web.cecs.pdx.edu/~strom/ev2/articles/Gover_slides_tutorial 