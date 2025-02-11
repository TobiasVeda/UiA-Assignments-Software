using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using assignment_4.Data;
using assignment_4.Models;

namespace assignment_4;

public class Program{
    public static void Main(string[] args){
        var builder = WebApplication.CreateBuilder(args);

        // Add services to the container.
        var connectionString = builder.Configuration.GetConnectionString("DefaultConnection") ??
                               throw new InvalidOperationException("Connection string 'DefaultConnection' not found.");
        builder.Services.AddDbContext<ApplicationDbContext>(options =>
            options.UseSqlite(connectionString));
        builder.Services.AddDatabaseDeveloperPageExceptionFilter();

        builder.Services.AddDefaultIdentity<ApplicationUser>(options => options.SignIn.RequireConfirmedAccount = true)
            .AddRoles<IdentityRole>() //<===Added=========================================
            .AddEntityFrameworkStores<ApplicationDbContext>();
        
        builder.Services.AddControllersWithViews();

        var app = builder.Build();

        using (var services = app.Services.CreateScope()){
            
            var db = services.ServiceProvider.GetRequiredService<ApplicationDbContext>();
            ApplicationDbInitializer.Initialize(db);
        }
        
        // Configure the HTTP request pipeline.
        if (app.Environment.IsDevelopment()){
            app.UseMigrationsEndPoint();
        }
        else{
            app.UseExceptionHandler("/Home/Error");
            // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
            app.UseHsts();
        }

        app.UseHttpsRedirection();
        app.UseStaticFiles();

        app.UseRouting();

        app.UseAuthorization();

        app.MapControllerRoute(
            name: "default",
            pattern: "{controller=Home}/{action=Index}/{id?}");
        app.MapRazorPages();

        app.Run();
    }
}