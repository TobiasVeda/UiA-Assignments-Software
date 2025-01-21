namespace assignment_4.Data;

using assignment_4.Models;

public static class ApplicationDbInitializer{
    
    public static void Initialize(ApplicationDbContext db)
    {
        // Delete the database before we initialize it. This is common to do during development.
        db.Database.EnsureDeleted();

        // Recreate the database and tables according to our models
        db.Database.EnsureCreated();

        // const bool testing = true;
        const bool testing = false;
        if (testing){
            var blogs = new[]
            {
                new Blog("nick1", "title1", "summary1", "content2", System.DateTime.Now),
                new Blog("nick2", "title2", "summary2", "content2", System.DateTime.Now)
            };
            
            db.Blogs.AddRange(blogs);
        }
        
        // Finally save the added entities
        db.SaveChanges();
    }
    
    
}