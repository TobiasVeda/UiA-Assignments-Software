using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using assignment_4.Models;

namespace assignment_4.Data;

public class ApplicationDbContext : IdentityDbContext<ApplicationUser>{
    public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
        : base(options){
    }
    public DbSet<Blog> Blogs => Set<Blog>();
}