from django.urls import path
from . import views

urlpatterns = [
    path('', views.landing_page, name='landing'),
    path('public-emergency/', views.public_emergency, name='public_emergency'),
    path('login/', views.login_view, name='login'),
    path('signup/', views.signup_view, name='signup'),
    path('logout/', views.logout_view, name='logout'),
    path('dashboard/', views.dashboard_redirect, name='dashboard_redirect'),
    path('profile/', views.profile_view, name='profile'),
    
    # Dashboards
    path('dashboard/admin/', views.admin_dashboard, name='admin_dashboard'),
    path('dashboard/doctor/', views.doctor_dashboard, name='doctor_dashboard'),
    path('dashboard/nurse/', views.nurse_dashboard, name='nurse_dashboard'),
    path('dashboard/receptionist/', views.receptionist_dashboard, name='receptionist_dashboard'),
    path('dashboard/pharmacist/', views.pharmacist_dashboard, name='pharmacist_dashboard'),
    path('dashboard/laboratory/', views.lab_dashboard, name='lab_dashboard'),
    path('dashboard/accountant/', views.accountant_dashboard, name='accountant_dashboard'),
    path('dashboard/patient/', views.patient_dashboard, name='patient_dashboard'),
    path('dashboard/patient/details/', views.patient_my_details, name='patient_my_details'),
    path('dashboard/patient/prescriptions/', views.patient_my_prescriptions, name='patient_my_prescriptions'),
    
    # Admin verification
    path('dashboard/admin/pending-requests/', views.pending_requests, name='pending_requests'),
    path('dashboard/admin/pending-requests/<int:profile_id>/approve/', views.approve_staff, name='approve_staff'),
    path('dashboard/admin/pending-requests/<int:profile_id>/reject/', views.reject_staff, name='reject_staff'),

    # Patient CRUD
    path('patients/', views.patient_list, name='patient_list'),
    path('patients/new/', views.patient_create, name='patient_create'),
    path('patients/<int:pk>/', views.patient_detail, name='patient_detail'),
    path('patients/<int:pk>/delete/', views.patient_delete, name='patient_delete'),
    path('patients/<int:patient_id>/vitals/', views.record_vitals, name='record_vitals'),

    # Appointments
    path('appointments/book/', views.appointment_book, name='appointment_book'),

    # Rooms & Beds
    path('rooms/', views.manage_rooms, name='manage_rooms'),
    path('rooms/new/', views.room_create, name='room_create'),
    path('rooms/<int:room_id>/edit/', views.room_update, name='room_update'),
    path('rooms/<int:room_id>/delete/', views.room_delete, name='room_delete'),
    path('rooms/pricing/', views.manage_pricing, name='manage_pricing'),
    path('rooms/<int:room_id>/beds/new/', views.bed_create, name='bed_create'),
    path('beds/<int:bed_id>/edit/', views.bed_update, name='bed_update'),
    path('beds/<int:bed_id>/allocate/', views.bed_allocate, name='bed_allocate'),
    path('beds/<int:bed_id>/delete/', views.bed_delete, name='bed_delete'),

    # Ventilator sessions
    path('ventilator/', views.ventilator_sessions, name='ventilator_sessions'),
    path('ventilator/new/', views.ventilator_create, name='ventilator_create'),
    path('ventilator/<int:pk>/', views.ventilator_detail, name='ventilator_detail'),

    # Invoices & Billing
    path('billing/', views.billing_list, name='billing_list'),
    path('billing/new/', views.billing_create, name='billing_create'),
    path('billing/api/patient-data/<int:patient_id>/', views.get_patient_billing_data, name='get_patient_billing_data'),

    # Inventory Stock
    path('inventory/', views.inventory_list, name='inventory_list'),
    path('inventory/new/', views.inventory_create, name='inventory_create'),
    path('inventory/<int:pk>/edit/', views.inventory_update, name='inventory_update'),
    path('inventory/<int:pk>/delete/', views.inventory_delete, name='inventory_delete'),

    # Laboratory reports
    path('lab-test/new/', views.lab_test_create, name='lab_test_create'),
    path('patients/<int:patient_id>/lab-test/new/', views.lab_test_create, name='lab_test_create_for_patient'),
    path('lab-test/<int:pk>/update/', views.lab_test_update, name='lab_test_update'),

    # Punch attendance
    path('attendance/', views.punch_attendance, name='punch_attendance'),

    # Emergencies & dispatch
    path('emergency/', views.trigger_emergency, name='trigger_emergency'),
    path('ambulances/', views.ambulance_dispatch, name='ambulance_dispatch'),
    path('ambulances/new/', views.ambulance_create, name='ambulance_create'),
    path('ambulances/<int:amb_id>/delete/', views.ambulance_delete, name='ambulance_delete'),
]
