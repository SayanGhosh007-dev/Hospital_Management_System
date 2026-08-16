# hms_app/utils.py

import logging

logger = logging.getLogger(__name__)

def send_sms_notification(phone_number, message):
    """
    Production-Ready Mock SMS Engine.
    Simulates sending an SMS by printing to the server console.
    When a third-party gateway (Twilio, AWS SNS, Vonage) is configured,
    plug the API calls in here.
    """
    if not phone_number:
        return False

    formatted_log = (
        "\n" + "="*50 + "\n"
        f"📱 [OUTBOUND SMS DISPATCHED]\n"
        f"To: {phone_number}\n"
        f"Message: {message}\n"
        + "="*50 + "\n"
    )
    
    # Print securely to standard output for visibility in terminal
    print(formatted_log)
    
    # Also log it for production monitoring
    logger.info(f"SMS Sent to {phone_number}: {message}")
    
    return True
