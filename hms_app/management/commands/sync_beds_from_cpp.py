import json
import os
from django.core.management.base import BaseCommand, CommandError
from hms_app.models import Room, Bed

class Command(BaseCommand):
    help = 'Sync bed configuration from C++ generated JSON file (data/bed_config.json)'

    def handle(self, *args, **options):
        json_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../data/bed_config.json'))
        if not os.path.exists(json_path):
            raise CommandError(f'JSON file not found at {json_path}')
        with open(json_path, 'r') as f:
            try:
                config = json.load(f)
            except json.JSONDecodeError as e:
                raise CommandError(f'Invalid JSON: {e}')
        # Clear existing beds (optional: could also clear rooms)
        Bed.objects.all().delete()
        # Optional: we could also clear rooms that are not needed
        for entry in config:
            room_number = entry.get('room_number')
            room_type = entry.get('room_type', 'General')
            beds_count = entry.get('beds', 1)
            if room_number is None:
                self.stdout.write(self.style.WARNING('Skipping entry without room_number'))
                continue
            # Get or create the room
            room, created = Room.objects.get_or_create(
                room_number=room_number,
                defaults={
                    'room_type': room_type,
                    'charges': 0.0,
                    'status': 'Available',
                }
            )
            if not created:
                # Update type if needed
                room.room_type = room_type
                room.save()
            # Create beds for this room
            for i in range(1, beds_count + 1):
                Bed.objects.create(
                    room=room,
                    bed_number=str(i),
                    category='General',
                    status='Available',
                )
        self.stdout.write(self.style.SUCCESS(f'Successfully synced {len(config)} rooms and created corresponding beds.'))
