using assignment_4.Models;
using assignment_4.Data;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;

namespace assignment_4.Controllers;

public class BlogController : Controller{
    
    private readonly ApplicationDbContext _db;
    private UserManager<ApplicationUser> _um;
    private RoleManager<IdentityRole> _rm;

    public BlogController(ApplicationDbContext db, UserManager<ApplicationUser> um, RoleManager<IdentityRole> rm){
        _db = db;
        _um = um;
        _rm = rm;
        
        var adminUser = new ApplicationUser { Nickname = "Nickname", UserName = "abc@uia.no", Email = "abc@uia.no", EmailConfirmed = true};
        _um.CreateAsync(adminUser, "Password1.").Wait();
        
        // _rm.CreateAsync(new IdentityRole("Admin")).Wait();
        // _um.AddToRoleAsync(adminUser, "Admin").Wait();
    }
    

    
    [HttpGet]
    [AllowAnonymous]
    public IActionResult Index(){
        var blogs = _db.Blogs.ToList();
        blogs = blogs.OrderBy(o => o.Time).ToList();
        blogs.Reverse();
        
        return View(blogs);
    }
    
    [HttpPost]
    [AllowAnonymous]
    public IActionResult Index(int i_id){
 
        return RedirectToAction("Edit", new {id = i_id});
    }
    
    
    [HttpGet]
    [Authorize]
    public IActionResult Add(){
        var user = _um.GetUserAsync(User).Result;
        ViewBag.Nickname = user.Nickname;

        return View();
    }
    
    [HttpPost]
    public IActionResult Add(Blog blog){
        if (ModelState.IsValid){
            _db.Blogs.Add(blog);
            _db.SaveChanges();
        }
        return RedirectToAction(nameof(Index));
    }
    
    [HttpGet]
    [Authorize]
    public IActionResult Edit(int id){
        
        if (ModelState.IsValid){
            var blog = new Blog();
        
            foreach (var i in _db.Blogs){
                if (i.Id == id){
                    blog = i;
                }
            }
            
            var user = _um.GetUserAsync(User).Result;
            if (user.Nickname == blog.Nickname){
                return View(blog);
            }
        }
            
        return RedirectToAction(nameof(Index));
    }
    [HttpPost]
    [Authorize]
    public IActionResult Edit(Blog blog){

        if (ModelState.IsValid){
            
            _db.Update(blog);
            _db.SaveChanges();
        }
        
        return RedirectToAction(nameof(Index));
    }
}