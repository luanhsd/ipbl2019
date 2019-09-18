﻿using STAGIOPTR.Models;
using STAGIOPTR.Database;
using Xamarin.Forms;

namespace STAGIOPTR.ViewModels
{
    public class PatientUpdateViewModel : BaseViewModel
    {
        private Patient _patient;

        public Patient Patient
        {
            get { return _patient; }
            set { SetProperty(ref _patient, value); }
        }

        DatabaseConnection database = new DatabaseConnection();

        public Command UpdatePatientCommand { get; }

        public PatientUpdateViewModel()
        {

        }

        public PatientUpdateViewModel(Patient Patient)
        {
            this.Patient = Patient;
            UpdatePatientCommand = new Command(ExecuteUpdatePatientCommand);
        }

        public void ExecuteUpdatePatientCommand()
        {
            this.database.UpdatePatient(this.Patient);
        }
    }
}
