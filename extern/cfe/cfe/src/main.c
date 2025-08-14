#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmi.h"
#include "bmi_cfe.h"
#include "cfe.h"

/*
This main program is a mock framwork.
This is not part of BMI, but acts as the driver that calls the model.
*/
int
 main(int argc, const char *argv[])
{
  
  ////////////////////////////////////////////////////////////////
  //////////////    USING UPDATE    //////////////////////////////
  ////////////////////////////////////////////////////////////////
  //////////////    USING UPDATE    //////////////////////////////
  ////////////////////////////////////////////////////////////////
  //////////////    USING UPDATE    //////////////////////////////
  ////////////////////////////////////////////////////////////////
  printf("Running CFE using Update\n");
  printf("_____________________________\n");

  // A configuration file is required for running this model through BMI
  if(argc<=1){
    printf("make sure to include a path to the config file\n");
    exit(1);
  }

   printf("allocating memory to store entire BMI structure for CFE\n");
  // allocating memory to store the entire BMI structure for CFE
  Bmi *cfe_bmi_model = (Bmi *) malloc(sizeof(Bmi));

  printf("Registering BMI CFE model\n");
  register_bmi_cfe(cfe_bmi_model);

  printf("Initializeing BMI CFE model\n");
  const char *cfg_file = argv[1];
  cfe_bmi_model->initialize(cfe_bmi_model, cfg_file);

  printf("Get the information from the configuration here in Main\n");
  // Get the information from the configuration here in Main  
  cfe_state_struct *cfe_main_data;
  cfe_main_data = (cfe_state_struct *) cfe_bmi_model->data;

  printf("looping through and calling update\n");
  if (cfe_main_data->verbosity > 0)
      print_cfe_flux_header();

  for (int i = 0; i < 51840; i++){

    cfe_bmi_model->update(cfe_bmi_model);
    //print_cfe_flux_at_timestep(cfe_main_data);
    //mass_balance_check(cfe_main_data);

    if (cfe_main_data->verbosity > 0)
        print_cfe_flux_at_timestep(cfe_main_data);
  }


  // Run the Mass Balance check
  mass_balance_check(cfe_main_data); 

void print_cfe_state_struct(struct cfe_state_struct* state) {
    printf("Size of cfe_state_struct: %zu bytes\n", sizeof(struct cfe_state_struct));

    printf("timestep_rainfall_input_m: %f\n", state->timestep_rainfall_input_m);
    printf("soil_reservoir_storage_deficit_m: %f\n", state->soil_reservoir_storage_deficit_m);
    printf("infiltration_depth_m: %f\n", state->infiltration_depth_m);
    printf("infiltration_excess_m (ptr): %p\n", (void*)state->infiltration_excess_m);
    printf("gw_reservoir_storage_deficit_m: %f\n", state->gw_reservoir_storage_deficit_m);
    printf("timestep_h: %f\n", state->timestep_h);

    printf("epoch_start_time: %ld\n", state->epoch_start_time);
    printf("num_timesteps: %d\n", state->num_timesteps);
    printf("current_time_step: %d\n", state->current_time_step);
    printf("time_step_size: %d\n", state->time_step_size);
    printf("time_step_fraction: %f\n", state->time_step_fraction);
    printf("is_forcing_from_bmi: %d\n", state->is_forcing_from_bmi);
    printf("forcing_file (ptr): %p\n", (void*)state->forcing_file);

    printf("K_lf: %f\n", state->K_lf);
    printf("K_nash_subsurface: %f\n", state->K_nash_subsurface);
    printf("N_nash_subsurface: %d\n", state->N_nash_subsurface);

    printf("num_giuh_ordinates: %d\n", state->num_giuh_ordinates);
    printf("surface_runoff_scheme: %d\n", state->surface_runoff_scheme);
    printf("nwm_ponded_depth_m: %f\n", state->nwm_ponded_depth_m);

    printf("forcing_data_precip_kg_per_m2 (ptr): %p\n", (void*)state->forcing_data_precip_kg_per_m2);
    printf("forcing_data_time (ptr): %p\n", (void*)state->forcing_data_time);

    printf("giuh_ordinates (ptr): %p\n", (void*)state->giuh_ordinates);
    printf("nash_storage_subsurface (ptr): %p\n", (void*)state->nash_storage_subsurface);
    printf("runoff_queue_m_per_timestep (ptr): %p\n", (void*)state->runoff_queue_m_per_timestep);

    printf("flux_direct_runoff_m (ptr): %p\n", (void*)state->flux_direct_runoff_m);
    printf("flux_nash_lateral_runoff_m (ptr): %p\n", (void*)state->flux_nash_lateral_runoff_m);
    printf("flux_from_deep_gw_to_chan_m (ptr): %p\n", (void*)state->flux_from_deep_gw_to_chan_m);
    printf("flux_perc_m (ptr): %p\n", (void*)state->flux_perc_m);
    printf("flux_lat_m (ptr): %p\n", (void*)state->flux_lat_m);
    printf("flux_Qout_m (ptr): %p\n", (void*)state->flux_Qout_m);

    printf("verbosity: %d\n", state->verbosity);
}
 
  //printf("print cfe_state_struct size and variables\n");
  //print_cfe_state_struct(cfe_main_data);
  //printf("the end of the print cfe_state_struct\n");

  printf("Finalizing CFE model\n");
  cfe_bmi_model->finalize(cfe_bmi_model);

  ////////////////////////////////////////////////////////////////
  //////////////    USING UPDATE UNTIL    ////////////////////////
  ////////////////////////////////////////////////////////////////
  //////////////    USING UPDATE UNTIL    ////////////////////////
  ////////////////////////////////////////////////////////////////
  //////////////    USING UPDATE UNTIL    ////////////////////////
  ////////////////////////////////////////////////////////////////
  printf("Running CFE using UPDATE UNTIL\n");
  printf("_____________________________\n");
  
  printf("allocating memory to store entire BMI structure for CFE\n");
  // allocating memory to store the entire BMI structure for CFE
  Bmi *cfe_bmi_model2 = (Bmi *) malloc(sizeof(Bmi));

  printf("Registering BMI CFE model\n");
  register_bmi_cfe(cfe_bmi_model2);

  printf("Initializeing BMI CFE model\n");
  const char *cfg_file2 = argv[1];
  cfe_bmi_model2->initialize(cfe_bmi_model2, cfg_file2);

  printf("Get the information from the configuration here in Main\n");
  // Get the information from the configuration here in Main  
  cfe_state_struct *cfe_main_data2;
  cfe_main_data2 = (cfe_state_struct *) cfe_bmi_model2->data;

  /*************************************************************************
   This will be used to advance the model with update_until
  **************************************************************************/
  double model_time_step_size;
  cfe_bmi_model2->get_time_step(cfe_bmi_model2, &model_time_step_size);
  printf("The model time step size is: %lf\n", model_time_step_size);

  printf("Calling update_until()\n");
  if (cfe_main_data2->verbosity > 0)
      print_cfe_flux_header();

  // Run the model with the update until function
  cfe_bmi_model2->update_until(cfe_bmi_model2, 51840*model_time_step_size);

  if (cfe_main_data2->verbosity > 0)
      print_cfe_flux_at_timestep(cfe_main_data2);

  // Run the Mass Balance check
  //mass_balance_check(cfe_main_data);

  printf("Finalizing CFE model\n");
  cfe_bmi_model2->finalize(cfe_bmi_model2);


  /////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////

  return 0;
}
