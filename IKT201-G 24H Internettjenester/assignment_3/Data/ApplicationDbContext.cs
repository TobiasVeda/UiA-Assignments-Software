using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace assignment_3.Data;

public class ApplicationDbContext : IdentityDbContext{
    public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
        : base(options){
    }
    
    public DbSet<Models.Guest> Guests{ get; set; }
}