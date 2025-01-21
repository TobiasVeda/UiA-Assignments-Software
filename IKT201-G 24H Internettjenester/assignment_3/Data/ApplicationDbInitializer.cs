namespace assignment_3.Data;

using assignment_3.Models;

public static class ApplicationDbInitializer{
    
    public static void Initialize(ApplicationDbContext db)
    {
        // Delete the database before we initialize it. This is common to do during development.
        db.Database.EnsureDeleted();

        // Recreate the database and tables according to our models
        db.Database.EnsureCreated();

        const bool testing = false;
        if (testing){
            var guests = new[]
            {
                new Guest("name1", "title1", "message1"),
                new Guest("name2", "title2", "message2")
            };
            
            db.Guests.AddRange(guests);
        }
        
        // Finally save the added entities
        db.SaveChanges();
    }
    
    
}